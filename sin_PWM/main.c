#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include "math.h"
void Port_Init()
{
	GPIO_InitTypeDef Gpio_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	Gpio_InitStructure.GPIO_Pin=0xFF00;
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	Gpio_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOE,&Gpio_InitStructure);

	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_0;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	Gpio_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&Gpio_InitStructure);
}

void _delay(uint32_t i)
{
	uint32_t j=0;
	i*=7.2;
	for(j=0;j<=i;j++)
		{};
}

void PWM(uint8_t *a)
{
	int i=0;
	GPIOE->ODR|=0xFF00;
	while (i<100)
	{
	if (i==*(a+0)) GPIOE->ODR &=~(1<<8);
	if (i==*(a+1)) GPIOE->ODR &=~(1<<9);
	if (i==*(a+2)) GPIOE->ODR &=~(1<<10);
	if (i==*(a+3)) GPIOE->ODR &=~(1<<11);
	if (i==*(a+4)) GPIOE->ODR &=~(1<<12);
	if (i==*(a+5)) GPIOE->ODR &=~(1<<13);
	if (i==*(a+6)) GPIOE->ODR &=~(1<<14);
	if (i==*(a+7)) GPIOE->ODR &=~(1<<15);
	i++;
	}
}

int main(void)
{
	uint8_t a[8];
	uint8_t k;
	double t=1.0005;
	uint16_t f=0;
	Port_Init();

    while(1)
    {

    	if (((GPIOA->IDR&(1<<0))==1)&&(f==0))
    		{
    			GPIO_ResetBits(GPIOE,0xFF00);
    			f=1;
    		}
    		else
    			{
    			for(k=0;k<8;++k)
    				a[k]=50*(1+sinf(6.28*1*t+k*6.28/8));
    			PWM(a);
    			t-=0.0005;
    			if(t<0) t=1;
    			}
    	if (((GPIOA->IDR&(1<<0))==1)&&(f==1))
    	    {
    	    		f=0;
    	    }
    }
}
