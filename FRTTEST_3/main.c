#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

struct param
{
unsigned char x;
unsigned char y;
unsigned char z;
unsigned int t;
};

struct param args = {8, 9, 10, 300};
GPIO_InitTypeDef GPIO_InitStructure;

void Port_Init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = 0xFF00;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Task(void *pvParameters)
{
	while (1)
	{
		GPIOE->ODR ^= (1 << ((struct param*) pvParameters)->x)|
				 (1 << ((struct param*) pvParameters)->y)|
				 (1 << ((struct param*) pvParameters)->z);
		vTaskDelay(((struct param*) pvParameters)->t);
	}
}

int main(void)
{
	Port_Init();
	xTaskCreate(Task, (signed char *) "task", configMINIMAL_STACK_SIZE, &args,
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
