#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <semihosting.h>
void Port_Init()
{
	GPIO_InitTypeDef Gpio_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	Gpio_InitStructure.GPIO_Pin=0xFF00;
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	Gpio_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOE,&Gpio_InitStructure);
}
int main(void)
{
	unsigned char k;
	Port_Init();
    while(1)
    {
    	k=SH_GetChar()-'0';
    	if (k<=8)
    	{
    		GPIOE->ODR^=1<<(k+7);
    		SH_SendChar(k);
    	}
    }
}
