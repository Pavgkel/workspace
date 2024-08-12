#include <stm32f30x_gpio.h>
#include <stm32f30x_misc.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>
#include <stm32f30x.h>




void GPIO_INIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_Level_1;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void NVIC_INIT()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM_INIT()
{
	TIM_TimeBaseInitTypeDef Tim_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	Tim_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	Tim_InitStructure.TIM_Prescaler=36000;
	Tim_InitStructure.TIM_Period=1000;
	TIM_TimeBaseInit(TIM7,&Tim_InitStructure);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM7,ENABLE);
}
void TIM_IRQHandler(void)
{
	GPIOE->ODR^=(1<<9);
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);

}
int main(void)
{
	GPIO_INIT();
	NVIC_INIT();
	TIM_INIT();
    while(1)
    {

    }
}
