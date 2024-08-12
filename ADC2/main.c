#include <stm32f30x.h>
#include <stm32f30x_adc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_misc.h>


volatile uint16_t V = 0;
volatile uint8_t delay = 0;

void GPIO_INIT()
{
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = 1<<9;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOE, &GPIO_InitStructure) ;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_INIT()
{
ADC_InitTypeDef ADC_InitStructure;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div6) ;
ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_9;
ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
ADC_InitStructure.ADC_NbrOfRegChannel =1;
ADC_Init(ADC1, &ADC_InitStructure);
ADC_RegularChannelConfig(ADC1, 1, 1, ADC_SampleTime_7Cycles5);
ADC_ExternalTriggerConfig(ADC1, ADC_ExternalTrigConvEvent_9, ADC_ExternalTrigEventEdge_RisingEdge);
ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
ADC_Cmd(ADC1, ENABLE);
}

void TIM_INIT()
{
TIM_TimeBaseInitTypeDef timer;
RCC_ClocksTypeDef RCC_Clocks;
RCC_GetClocksFreq(&RCC_Clocks) ;
SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000) ;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
timer.TIM_Prescaler = 36000;
timer.TIM_Period = 20;
timer.TIM_CounterMode=TIM_CounterMode_Up;
TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
TIM_TimeBaseInit(TIM1, &timer);
TIM_Cmd(TIM1, ENABLE);
}

void SysTick_Handler (void)
{
if(delay == 0) GPIOE->ODR |= 1<<9;
if(delay == V) GPIOE->ODR &= ~(1<<9);
delay++;
if(delay == 128) delay = 0;
}

void ADC1_2_IRQHandler()
{
V = ADC_GetConversionValue(ADC1) >>5;
ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}

int main(void)
{
	GPIO_INIT();
	ADC_INIT();
	TIM_INIT();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC_StartConversion(ADC1);
	while(1)
	{ }
}
