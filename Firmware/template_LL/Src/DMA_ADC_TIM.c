#include "main.h"
#include "DMA_ADC_TIM.h"

uint8_t USB_Transfer_Enable_Flag=0;    //USB��ʼ����ADC���ݵı�־��0�����䣬1����
uint8_t DMA_ADC_Enable_Flag = 0;       //DMA��ADC��ʼʹ�ܱ�־��Ҫ�ɼ�������1���ر���0
//__align(16) uint16_t ADC_Value_Buffer[ADC_BUFFER_SIZE] __attribute__((at(0x24000200)));   //������λ�ö�����0x24000200��
uint16_t ADC_Value_Buffer[ADC_BUFFER_SIZE];


void DMA_ADC_TIM_Init(void)
{
	//�ȹص���ʱ��1
	LL_TIM_DisableCounter(TIM1);
	//��ʼ��DMA������ص�����
	LL_DMA_DisableDoubleBufferMode(DMA1,LL_DMA_STREAM_0);                               //�ص�˫bufferģʽ
	LL_DMA_SetStreamPriorityLevel(DMA1,LL_DMA_STREAM_0,LL_DMA_PRIORITY_VERYHIGH);              //����DMA�����ȼ�
	LL_DMA_ConfigAddresses(DMA1,LL_DMA_STREAM_0,(uint32_t)&ADC1->DR, (uint32_t)ADC_Value_Buffer,LL_DMA_DIRECTION_PERIPH_TO_MEMORY);        //����Դ��ַ�������ַ
	LL_DMA_EnableIT_TC(DMA1,LL_DMA_STREAM_0);                                            //����DMA��������ж�
	//��ʼ��ADC������ص�����
	
	LL_ADC_REG_SetDataTransferMode(ADC1,LL_ADC_REG_DMA_TRANSFER_LIMITED);            //�ٿص�ADC��CFGR�Ĵ�����DMNGT�� ����ѡ��DMA����ģʽ��DFSDMģʽ��DMAѭ��ģʽ�ȡ� ��RM0443��845ҳ��˵����������DMA����Ϊ����̶���Ŀ�����ݣ�Ӧѡ���ģʽ��
	LL_ADC_StartCalibration(ADC1,LL_ADC_CALIB_OFFSET_LINEARITY,LL_ADC_SINGLE_ENDED);        //ͬʱ����ƫ�ƺ����Զ�У����16384��ʱ������   У��ʱADC����û��ʹ��
	while(LL_ADC_IsCalibrationOnGoing(ADC1)==1);                              //�ȴ�ADCУ׼���
}

void DMA_ADC_TIM_Enable(void)
{
	DMA_ADC_Enable_Flag=0;
	
	LL_DMA_ClearFlag_TC0(DMA1);                                //���DMA�жϱ�־ LISR TCIF0
	LL_DMA_SetDataLength(DMA1,LL_DMA_STREAM_0,ADC_BUFFER_SIZE);                            //���ô����������
	LL_DMA_EnableStream(DMA1,LL_DMA_STREAM_0);                                             //ʹ��DMA1
	
	LL_ADC_REG_StartConversion(ADC1);                               //��ʼת�����ȴ������¼�

	LL_ADC_Enable(ADC1);
	

	LL_TIM_EnableCounter(TIM1);                //������ʱ��
}

void DMA_ADC_TIM_Disable(void)
{
	LL_TIM_DisableCounter(TIM1);            //�رն�ʱ��
	LL_DMA_DisableStream(DMA1,LL_DMA_STREAM_0);
	LL_ADC_Disable(ADC1);
}


