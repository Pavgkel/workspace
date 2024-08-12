#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
GPIO_InitTypeDef GPIO_InitStructure;
uint16_t f=0;

void _delay(uint32_t i)
{
	uint32_t j = 0;
	i *= 7.2;
	for (j = 0; j <= i; j++)
	{
	};
}
void GPIO_INIT()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
	GPIO_INIT();
    while(1)
    {
		if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) == 1)
		{
			_delay(50000);

			if ((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)) == 1)
			{
				if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8) == 1)
				{
					GPIO_ResetBits(GPIOE, GPIO_Pin_8);
				}
				else
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
				while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) == 1)
				{
				};
			}
		}

//    	if (((GPIOA->IDR&(1<<0))==1)&&(f==0))
//    	{
//    		_delay(100000);
//
//    		if (((GPIOA->IDR & (1<<0))==1)&& (f==0))
//    		{
//    			GPIOE->ODR^=(1<<8);
//    			f=1;
//    		}
//    	}
//    	if (((GPIOA->IDR&(1<<0))==1)&&(f==1))
//    	{
//    		f=0;
//    	}
    }
}
