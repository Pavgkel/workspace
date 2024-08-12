#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_misc.h>
#include <stm32f30x_usart.h>

uint8_t f = 0;

uint8_t k = 0;

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

void GPIO_USART1_Init();

void GPIO_USART2_Init();

void GPIO_LED_Init();

void GPIO_Button_Init();

void USART1_SendData(uint8_t ch);
void _delay(uint32_t i);

void button_scan();

void GPIO_USART1_Init()
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

USART_StructInit(&USART_InitStructure) ;
USART_InitStructure.USART_BaudRate = 9600;
USART_Init(USART1, &USART_InitStructure);

USART_Cmd(USART1, ENABLE);
}

void GPIO_USART2_Init()
{
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);

USART_StructInit (&USART_InitStructure) ;
USART_InitStructure.USART_BaudRate = 9600;
USART_Init(USART2, &USART_InitStructure) ;

USART_Cmd(USART2, ENABLE) ;
USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
NVIC_EnableIRQ(USART2_IRQn);
}

void GPIO_LED_Init()
{
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

GPIO_InitStructure.GPIO_Pin = 0xFF00;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void GPIO_Button_Init()
{
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Init(GPIOA, &GPIO_InitStructure) ;
}

void USART1_SendData(uint8_t ch)
{
while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
USART_SendData(USART1, ch);
}

void USART2_IRQHandler()
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		GPIOE->ODR = 1 << (USART_ReceiveData(USART2) + 8);
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

void _delay(uint32_t i)
{
	uint32_t j = 0;
	i *= 7.2;
	for (j = 0; j <= i; j++)
	{
	};
}

void button_scan()
{
	if (((GPIOA->IDR & (1 << 0)) == 1) && (f == 0))
	{
		_delay(50000);
		if (((GPIOA->IDR & (1 << 0)) == 1) && (f == 0))
		{
			USART1_SendData((k++) % 8);
			f = 1;
		}
	}
	if (((GPIOA->IDR & (1 << 0)) == 0) && (f == 1))
	{
		f = 0;
	}
}

int main(void)
{
	GPIO_LED_Init();
	GPIO_Button_Init();
	GPIO_USART1_Init();
	GPIO_USART2_Init();

    while(1)
    {
    	button_scan();
    }
}
