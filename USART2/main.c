#include "stm32f30x.h"
uint8_t count =0;

void _delay(uint32_t i)
{
	uint32_t j = 0;
	i *= 7.2;
	for (j = 0; j <= i; j++)
	{
	}
}

void Send()
{
	while ((USART1->ISR & USART_ISR_TXE) == RESET)
	{
	};
	USART1->TDR = count % 8;
	count++;
}

void USART2_IRQHandler()
{
	if ((USART2->ISR & USART_ISR_RXNE) != RESET)
	{
		GPIOE->ODR = 1 << (USART2->RDR + 8);
	}
}
int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	GPIOA->MODER |= (2 << (3 * 2)) | (2 << (9 * 2));
	GPIOA->PUPDR |= (1 << (9 * 2));
	GPIOA->AFR[0] |= 7 << (3 * 4);
	GPIOA->AFR[1] |= 7 << (1 * 4);
	GPIOE->MODER |= (1 << 16) | (1 << 18) | (1 << 20) | (1 << 22) | (1 << 24)
			| (1 << 26) | (1 << 28) | (1 << 30);
	USART1->BRR = 7500;
	USART1->CR1 |= USART_CR1_UE | USART_CR1_TE;
	USART2->BRR = 3750;
	USART2->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_RXNEIE;
	NVIC->ISER[USART2_IRQn / 32] = 1 << (USART2_IRQn % 32);

	while (1)
	{
		Send();
		_delay(72000);
	}
}

