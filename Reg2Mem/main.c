#include <stm32f30x_adc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_dma.h>

uint32_t ADC_Result;
unsigned int result =0;

void _delay(uint32_t i)
{
uint32_t j=0;
i*=7.2;
for(j = 0;j<=i;j++){};
}

unsigned int readADC(uint8_t channel)
{
ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_7Cycles5);
ADC_StartConversion(ADC1);
return ADC_GetConversionValue(ADC1) ;
}

void PWM()
{
GPIOE->ODR |=(1<<9);
_delay(result);
GPIOE->ODR &=~(1<<9);
_delay(4095 - result);
}

void GPIO_INIT()
{
GPIO_InitTypeDef GPIO_Initstruct;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
GPIO_Initstruct.GPIO_Pin = GPIO_Pin_0;
GPIO_Initstruct.GPIO_Mode = GPIO_Mode_AN;
GPIO_Init(GPIOA, &GPIO_Initstruct);
GPIO_Initstruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Initstruct.GPIO_Pin=0xFF00;
GPIO_Initstruct.GPIO_OType = GPIO_OType_PP;
GPIO_Initstruct.GPIO_Speed = GPIO_Speed_Level_1;
GPIO_Initstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOE, &GPIO_Initstruct);
}

void DMA_INIT()
{

DMA_InitTypeDef DMA_InitStructure;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_Result;
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
}

void ADC_INIT()
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

ADC_Init(ADC1, &ADC_InitStructure);
}

int main(void)
{
	ADC_INIT();
	GPIO_INIT();
	DMA_INIT();
	ADC_Result = readADC(ADC_Channel_1);
	while (1)
	{
		PWM(ADC_Result);
	}

}
