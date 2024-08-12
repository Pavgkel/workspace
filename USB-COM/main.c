#include <hw_config.h>
#include <usb_lib.h>
#include <usb_desc.h>
#include <usb_pwr.h>

void LED_INIT()
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
GPIO_InitStructure.GPIO_Pin = 0xFF00;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Init(GPIOE, &GPIO_InitStructure);
}
int main(void)

{
	Set_System();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	LED_INIT();
	while (1)
	{
	}
}
