#include "led.h"

void Led_On(void)
{
	LL_GPIO_ResetOutputPin(LED_GPIO_Port,LED_Pin);          //��0��ʱ�����
}

void Led_Off(void)
{
	LL_GPIO_SetOutputPin(LED_GPIO_Port,LED_Pin);        //���ߣ�����
}

void LED_Toggle(void)          //LED״̬��ת
{
	LL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);       //��תGPIO
}

