#include "Exti_Key.h"



void Exti_Key_Timer_Init(void)
{
	//��������ݶ���STM32CubeMX�������ˣ�����Ҫ�����жϺ�ʹ�ܶ�ʱ���ͺ���
	LL_TIM_DisableCounter(TIM2);
	LL_TIM_ClearFlag_UPDATE(TIM2);     //����±�־
	LL_TIM_EnableIT_UPDATE(TIM2);    //���ж�
	//LL_TIM_EnableCounter(TIM2);            //�Ȳ�������ʱ�������ж����濪�ȽϺ�
}

