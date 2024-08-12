#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

void _delay(uint32_t i)
{
	uint32_t j=0;
	for (j=0;j<=i;j++){};
}

int main(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_8;
	//GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

    while(1)
    {
    	//GPIO_SetBits(GPIOE,GPIO_Pin_10);
    	//регистрами
    	GPIOE->ODR |= (1 << 10)|(1 << 8);
    	//GPIOE->ODR |= (1<<10);

    	_delay(3200000);
    	//GPIO_ResetBits(GPIOE,GPIO_Pin_10);
    	GPIOE->ODR &= ~( (1 << 10)|(1 << 8) );
    	//GPIOE->ODR &= ~(1<<10);
    	_delay(6400000);
    }
}
