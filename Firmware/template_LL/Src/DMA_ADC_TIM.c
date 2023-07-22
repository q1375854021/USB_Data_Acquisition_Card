#include "main.h"
#include "DMA_ADC_TIM.h"

uint8_t USB_Transfer_Enable_Flag=0;    //USB开始传输ADC数据的标志，0不传输，1传输
uint8_t DMA_ADC_Enable_Flag = 0;       //DMA和ADC开始使能标志，要采集数据置1，关闭置0
//__align(16) uint16_t ADC_Value_Buffer[ADC_BUFFER_SIZE] __attribute__((at(0x24000200)));   //把数组位置定义在0x24000200上
uint16_t ADC_Value_Buffer[ADC_BUFFER_SIZE];


void DMA_ADC_TIM_Init(void)
{
	//先关掉定时器1
	LL_TIM_DisableCounter(TIM1);
	//开始对DMA进行相关的配置
	LL_DMA_DisableDoubleBufferMode(DMA1,LL_DMA_STREAM_0);                               //关掉双buffer模式
	LL_DMA_SetStreamPriorityLevel(DMA1,LL_DMA_STREAM_0,LL_DMA_PRIORITY_VERYHIGH);              //设置DMA的优先级
	LL_DMA_ConfigAddresses(DMA1,LL_DMA_STREAM_0,(uint32_t)&ADC1->DR, (uint32_t)ADC_Value_Buffer,LL_DMA_DIRECTION_PERIPH_TO_MEMORY);        //配置源地址和外设地址
	LL_DMA_EnableIT_TC(DMA1,LL_DMA_STREAM_0);                                            //开启DMA传输完成中断
	//开始对ADC进行相关的配置
	
	LL_ADC_REG_SetDataTransferMode(ADC1,LL_ADC_REG_DMA_TRANSFER_LIMITED);            //操控的ADC的CFGR寄存器的DMNGT， 可以选择DMA单次模式，DFSDM模式，DMA循环模式等。 在RM0443的845页有说明，如果编程DMA设置为传输固定数目的数据，应选择此模式。
	LL_ADC_StartCalibration(ADC1,LL_ADC_CALIB_OFFSET_LINEARITY,LL_ADC_SINGLE_ENDED);        //同时进行偏移和线性度校正，16384个时钟周期   校正时ADC必须没有使能
	while(LL_ADC_IsCalibrationOnGoing(ADC1)==1);                              //等待ADC校准完成
}

void DMA_ADC_TIM_Enable(void)
{
	DMA_ADC_Enable_Flag=0;
	
	LL_DMA_ClearFlag_TC0(DMA1);                                //清除DMA中断标志 LISR TCIF0
	LL_DMA_SetDataLength(DMA1,LL_DMA_STREAM_0,ADC_BUFFER_SIZE);                            //设置传输的数据量
	LL_DMA_EnableStream(DMA1,LL_DMA_STREAM_0);                                             //使能DMA1
	
	LL_ADC_REG_StartConversion(ADC1);                               //开始转换，等待触发事件

	LL_ADC_Enable(ADC1);
	

	LL_TIM_EnableCounter(TIM1);                //开启定时器
}

void DMA_ADC_TIM_Disable(void)
{
	LL_TIM_DisableCounter(TIM1);            //关闭定时器
	LL_DMA_DisableStream(DMA1,LL_DMA_STREAM_0);
	LL_ADC_Disable(ADC1);
}


