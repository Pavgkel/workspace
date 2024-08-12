#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

volatile uint32_t delay=0;
volatile uint32_t delay2=0;

void SysTick_Handler (void)
{
	delay++;
	delay2++;
}

int main(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency/1000);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
    while(1)
    {
    	if (delay>700)
    	{
    		GPIOE->ODR^=(1<<8);
    		delay=0;
    	}
    	if (delay2>200)
    	   {
    	    GPIOE->ODR^=(1<<9);
    	    delay2=0;
    	   }
    }
}
