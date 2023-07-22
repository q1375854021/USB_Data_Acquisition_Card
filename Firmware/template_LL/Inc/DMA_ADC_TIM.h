#ifndef __DMA_ADC_TIM_H
#define __DMA_ADC_TIM_H

#include "main.h"

#define    ADC_BUFFER_SIZE    512

extern uint8_t USB_Transfer_Enable_Flag;    //USB开始传输ADC数据的标志，0不传输，1传输
extern uint8_t DMA_ADC_Enable_Flag ;       //DMA和ADC开始使能标志，要采集数据置1，关闭置0
extern uint16_t ADC_Value_Buffer[ADC_BUFFER_SIZE];




void DMA_ADC_TIM_Init(void);             //DMA和ADC初始化
void DMA_ADC_TIM_Enable(void);             //DMA和ADC使能
void DMA_ADC_TIM_Disable(void);               //DMA和ADC使能



#endif
