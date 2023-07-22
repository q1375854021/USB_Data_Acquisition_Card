#include "led.h"

void Led_On(void)
{
	LL_GPIO_ResetOutputPin(LED_GPIO_Port,LED_Pin);          //置0的时候灯亮
}

void Led_Off(void)
{
	LL_GPIO_SetOutputPin(LED_GPIO_Port,LED_Pin);        //拉高，灯灭
}

void LED_Toggle(void)          //LED状态反转
{
	LL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);       //反转GPIO
}

