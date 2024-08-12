#include <FreeRTOSConfig.h>
#include <projdefs.h>
#include <portmacro.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <croutine.h>
#include <task.h>
#include <queue.h>

int main(void)
{

    while(1)
    {
    }
}
void vApplicationIdleHook ( void ){} void vApplicationMallocFailedHook ( void ){for ( ;; );} void vApplicationStackOverflowHook ( xTaskHandle pxTask, signed char *pcTaskName ){ ( void ) pcTaskName; ( void ) pxTask; for ( ;; );}
void vApplicationTickHook ( void ){}
