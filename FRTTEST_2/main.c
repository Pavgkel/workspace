#include <FreeRTOS.h>
#include <task.h>
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <queue.h>

GPIO_InitTypeDef GPIO_InitStructure;
uint16_t m1[2] = {100, GPIO_Pin_9};
uint16_t m2[2] = {250, GPIO_Pin_13};

void Port_Init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void TaskLED(void *pvParameters)
{
	while (1)
	{
		GPIO_SetBits(GPIOE, *((uint16_t*) pvParameters + 1));
		vTaskDelay(*((uint16_t*) pvParameters));
		GPIO_ResetBits(GPIOE, *((uint16_t*) pvParameters + 1));
		vTaskDelay(*((uint16_t*) pvParameters));
	}
}

int main(void)
{
	Port_Init();
	xTaskCreate(TaskLED, (signed char *) "LED_1", configMINIMAL_STACK_SIZE, m1,
			2, (xTaskHandle *) NULL);
	xTaskCreate(TaskLED, (signed char *) "LED_2", configMINIMAL_STACK_SIZE, m2,
			2, (xTaskHandle *) NULL);
	vTaskStartScheduler(); // 3anyck weaynepa.
	while (1)
	{
	}
}

void vApplicationIdleHook ( void ){}
void vApplicationMallocFailedHook ( void ){for ( ;; );}
void vApplicationStackOverflowHook ( xTaskHandle pxTask, char *pcTaskName )
	{ ( void ) pcTaskName; ( void ) pxTask; for ( ;; );}
void vApplicationTickHook ( void ){}
