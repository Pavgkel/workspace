#include <stm32f30x.h>
#include <semihosting.h>

void Delay_ms(uint32_t nTime)
{
	uint32_t TimingDelay=nTime*5800;
	while (TimingDelay!=0){--TimingDelay;};
}
int main(void)
{
	char str[10];
	int t=0;
    while(1)
    {
    	sprintf(str,"t=%d\n",++t);
    	SH_SendString(str);
    	Delay_ms(1000);
    }
}
