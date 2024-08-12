#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_dma.h>
#include <stm32f30x_adc.h>

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef timer;
TIM_OCInitTypeDef timerPWM;

unsigned int readADC(uint8_t channel)
{
ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_7Cycles5);
ADC_StartConversion(ADC1) ;
return ADC_GetConversionValue(ADC1) ;
}

void gpio()
{
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
GPIO_Init(GPIOA, &GPIO_InitStruct);

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_2);
GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_2);
GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void tim()
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

timer.TIM_Prescaler = 36;
timer.TIM_Period = 4095;
timer.TIM_CounterMode = TIM_CounterMode_Up;

TIM_TimeBaseInit(TIM1, &timer);
TIM_Cmd(TIM1, ENABLE);
TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void pwm()
{
timerPWM.TIM_Pulse = 0;

timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
timerPWM.TIM_OutputState = TIM_OutputState_Enable;
timerPWM.TIM_OutputNState = TIM_OutputNState_Enable;
timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
timerPWM.TIM_OCNPolarity = TIM_OCPolarity_High;
timerPWM.TIM_OCIdleState = TIM_OCIdleState_Set;
timerPWM.TIM_OCNIdleState = TIM_OCNIdleState_Set;
TIM_OC1Init(TIM1, &timerPWM);
}

void adc()
{
ADC_InitTypeDef ADC_InitStructure;
ADC_CommonInitTypeDef ADC_CommonInitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div10) ;

ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;

ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_Circular;
ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;

ADC_CommonInit(ADC1, &ADC_CommonInitStructure) ;
ADC_DMACmd(ADC1, ENABLE);
ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);

ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
ADC_InitStructure.ADC_NbrOfRegChannel = 1;

ADC_Init(ADC1, &ADC_InitStructure) ;

ADC_Cmd(ADC1, ENABLE);
}

void dma()
{
DMA_InitTypeDef DMA_InitStructure;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&(TIM1->CCR1);
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
DMA_InitStructure.DMA_BufferSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
DMA_InitStructure.DMA_Priority = DMA_Priority_High;
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
DMA_Init(DMA1_Channel1, &DMA_InitStructure);
DMA_Cmd(DMA1_Channel1, ENABLE);
DMA_Cmd(DMA1_Channel2, ENABLE);
}

int main()
{
	gpio();
	adc();
	tim();
	pwm();
	dma();
	readADC(ADC_Channel_1);
	while (1)
	{
	}
}
