#ifndef __DMA_ADC_TIM_H
#define __DMA_ADC_TIM_H

#include "main.h"

#define    ADC_BUFFER_SIZE    512

extern uint8_t USB_Transfer_Enable_Flag;    //USB��ʼ����ADC���ݵı�־��0�����䣬1����
extern uint8_t DMA_ADC_Enable_Flag ;       //DMA��ADC��ʼʹ�ܱ�־��Ҫ�ɼ�������1���ر���0
extern uint16_t ADC_Value_Buffer[ADC_BUFFER_SIZE];




void DMA_ADC_TIM_Init(void);             //DMA��ADC��ʼ��
void DMA_ADC_TIM_Enable(void);             //DMA��ADCʹ��
void DMA_ADC_TIM_Disable(void);               //DMA��ADCʹ��



#endif
