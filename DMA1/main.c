#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_dma.h>

#define DMA_BUFF_SIZE 4

volatile uint16_t buff[DMA_BUFF_SIZE] = {0};
volatile uint16_t old_buff[DMA_BUFF_SIZE] = {0x0100, 0x0200,0x0400,0x0800};

void _delay(uint32_t i) {
	uint32_t j = 0;
	i *= 7.2;
	for (j = 0; j <= i; j++) {
	};
}

void DMA1_Channel1_IRQHandler(void)
{
	GPIOE->ODR ^= buff[0] | buff[1] | buff[2] | buff[3];
	DMA_ClearITPendingBit(DMA1_IT_TC1);
	DMA_Cmd(DMA1_Channel1, DISABLE);
}

void gpio()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = 0xFF00;
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
DMA_InitTypeDef DMA_MtoM;
void dma()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);


	DMA_MtoM.DMA_PeripheralBaseAddr = (uint32_t) & old_buff[0];
	DMA_MtoM.DMA_MemoryBaseAddr = (uint32_t) & buff[0];
	DMA_MtoM.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_MtoM.DMA_BufferSize = 4;

	DMA_MtoM.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_MtoM.DMA_MemoryInc = DMA_MemoryInc_Enable;

	DMA_MtoM.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_MtoM.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

	DMA_MtoM.DMA_Mode = DMA_Mode_Normal;
	DMA_MtoM.DMA_Priority = DMA_Priority_Medium;
	DMA_MtoM.DMA_M2M = DMA_M2M_Enable;
	DMA_Init(DMA1_Channel1, &DMA_MtoM);
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

int main(void)
{
	unsigned char f = 0;

	gpio();

	dma();

	while (1)
	{
		if (((GPIOA->IDR & (1 << 0)) == 1) && (f == 0))
		{
			_delay(50000);

			if (((GPIOA->IDR & (1 << 0)) == 1) && (f == 0))
			{
				DMA_Init(DMA1_Channel1, &DMA_MtoM);
				DMA_Cmd(DMA1_Channel1, ENABLE);
				f = 1;
			}
		}
		if (((GPIOA->IDR & (1 << 0)) == 0) && (f == 1))
		{
			f = 0;
		}
	}
}
