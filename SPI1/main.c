#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_spi.h>

void _delay(uint32_t i)
{
uint32_t j = 0;
i *= 7.2;
for(j = 0; j <= i; j++){};
}

void SPI2_IRQHandler()
{
	GPIOE->ODR = 1<<(SPI_ReceiveData8(SPI2)+8) ;
}

void GPIO_INIT()
{
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Init(GPIOA,&GPIO_InitStruct);
GPIO_InitStruct.GPIO_Pin=0xFF00;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_Init(GPIOE,&GPIO_InitStruct);
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStruct);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_5);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_5);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_5);
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOB, &GPIO_InitStruct);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_5);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_5);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_5);
}
void SPI_INIT()
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
SPI_InitTypeDef SPI_InitStruct;
SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_InitStruct.SPI_CRCPolynomial = 7;
SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
SPI_Init(SPI1, &SPI_InitStruct);
SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
SPI_Cmd(SPI1, ENABLE);

SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_InitStruct.SPI_CRCPolynomial = 7;
SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;
SPI_Init(SPI2, &SPI_InitStruct);
SPI_Cmd(SPI2, ENABLE) ;
SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
NVIC_EnableIRQ(SPI2_IRQn);
}

int main(void)
{
	unsigned char f = 0;
	unsigned char i = 0;
	GPIO_INIT();
	SPI_INIT();

	while (1)
	{
		if (((GPIOA->IDR & (1 << 0)) == 1) && (f == 0))
		{
			_delay(50000);
			if (((GPIOA->IDR & (1 << 0)) == 1) && (f == 0))
			{
				SPI_SendData8(SPI1, (i++) % 8);
				f = 1;
			}
		}
		if (((GPIOA->IDR & (1 << 0)) == 0) && (f == 1))
		{
			f = 0;
		}
	}
}
