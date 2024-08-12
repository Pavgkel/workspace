#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <math.h>
double a = 0;
GPIO_InitTypeDef GPIO_InitStructure;
void _delay(uint32_t i)
{
	uint32_t j=0;
	i*=7.2;
	for(j=0;j<=i;j++){};
}
void PWM (uint32_t tau, uint32_t T)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_11);
	_delay(tau);
	GPIO_ResetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_11);
	_delay(T-tau);
}
void GpioInit()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
int main(void)
{

	GpioInit();
    while(1)
    {
    	PWM((1+sinf(a))*500,1000);
    	a+=0.01;
    	if (a>=6.28) a=0;
    }
}
