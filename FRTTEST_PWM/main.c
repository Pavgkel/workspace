#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

int i = 0;
int a = 0;

void Port_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = 0xFF00;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void PWM(void *pvParameters)
{
	while (1)
	{
		GPIOE->ODR |= 1 << 9;
		while (i < 1e0)
		{
			if (i == a)
				GPIOE->ODR &= ~(1 << 9);
			i++;
		}
		i = 0;
	}
}

void PARAM(void *pvParameters)
{
	while (1)
	{
		++a;
		if (a == 100)
			a = 0;
		vTaskDelay(10);
	}
}

int main(void)
{
	Port_Init();
	xTaskCreate(PWM, (signed char *) "PWM", configMINIMAL_STACK_SIZE, NULL, 2,
			(xTaskHandle *) NULL);
	xTaskCreate(PARAM, (signed char *) "PARAM", configMINIMAL_STACK_SIZE, NULL,
			2, (xTaskHandle *) NULL);
	vTaskStartScheduler();

	while (1)
	{
	}
}
void vApplicationIdleHook ( void ){}
void vApplicationMallocFailedHook ( void ){for ( ;; );}
void vApplicationStackOverflowHook ( xTaskHandle pxTask, char *pcTaskName )
	{ ( void ) pcTaskName; ( void ) pxTask; for ( ;; );}
void vApplicationTickHook ( void ){}
