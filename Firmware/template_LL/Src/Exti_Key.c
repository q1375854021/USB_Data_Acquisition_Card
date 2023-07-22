#include "Exti_Key.h"



void Exti_Key_Timer_Init(void)
{
	//大多数内容都在STM32CubeMX中生成了，仅需要开启中断和使能定时器就好了
	LL_TIM_DisableCounter(TIM2);
	LL_TIM_ClearFlag_UPDATE(TIM2);     //清更新标志
	LL_TIM_EnableIT_UPDATE(TIM2);    //开中断
	//LL_TIM_EnableCounter(TIM2);            //先不开启定时器，在中断里面开比较好
}

