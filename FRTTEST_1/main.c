#include <FreeRTOS.h>
#include <task.h>
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <queue.h>

GPIO_InitTypeDef GPIO_InitStructure;

void Port_Init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void TaskLED1(void *pvParameters) //Qnycanye sagaym TaskLEDL
{
	while (1)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_15);

		vTaskDelay(500); // 3aaspxKa C NepexoAOM Ha APYLY® 3aRa4y.
		GPIO_ResetBits(GPIOE, GPIO_Pin_15);

		vTaskDelay(500); // 3agepxKa © NERSXOAOM Ha APRYEYS 2aRa4y

	}
}

void TaskLED2(void *pvParameters) //Qnycanme sagaum TaskLED2
{
	while (1)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_14);
		vTaskDelay(200); // 3aagpxKa c NERSXOAOM He ARYTYS 2aReHV
		GPIO_ResetBits(GPIOE, GPIO_Pin_14);
		vTaskDelay(200); // 3agepxKa c NEReXCAOM Ha AYE saAaYY.
	}
}

int main(void)
{
	Port_Init();
	xTaskCreate(TaskLED1, (signed char *) "LED1", configMINIMAL_STACK_SIZE,
			NULL, 2, (xTaskHandle *) NULL);
	xTaskCreate(TaskLED2, (signed char *) "LED2", configMINIMAL_STACK_SIZE,
			NULL, 2, (xTaskHandle *) NULL);
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
