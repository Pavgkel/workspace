#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_misc.h>

void GPIO_init()
{
GPIO_InitTypeDef GPIO_InitStruct;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_Init(GPIOE, &GPIO_InitStruct);

GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 ,GPIO_AF_2);
GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 ,GPIO_AF_2);
}

void TIM_init()
{
TIM_TimeBaseInitTypeDef TIM_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
TIM_InitStructure.TIM_Prescaler = 36000;
TIM_InitStructure.TIM_Period = 100;
TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM1, &TIM_InitStructure);
TIM_Cmd(TIM1, ENABLE);
TIM_CtrlPWMOutputs(TIM1, ENABLE);

TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void PWM_init()
{
TIM_OCInitTypeDef PWM_InitStructure;
PWM_InitStructure.TIM_Pulse = 100;
PWM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
PWM_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
PWM_InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
PWM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
PWM_InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
PWM_InitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
PWM_InitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
TIM_OC1Init(TIM1, &PWM_InitStructure) ;
}
void NVIC_init()
{
NVIC_InitTypeDef NVIC_InitStructure;

NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM16_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}

void TIM1_UP_TIM16_IRQHandler()
{
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	TIM1->CCR1 =70;
	//GPIOE->ODR^=(1<<8);
}

int main()
{
	GPIO_init();
	NVIC_init();
	TIM_init();

	PWM_init();

	while(1)
	{

	}
}
