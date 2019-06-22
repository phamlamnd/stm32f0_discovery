#include "systick.h"

void systick_init(void)
{
	/*Disable systick, clear flag*/
	STK->CSR = 0x00000000U;
	/*reset current value*/
	STK->CVR = 0x00000000U;	
	/*SysTick clksourse: processor*/
	STK->CSR |= 1U<<2;
}

void systick_interrupt_enable(unsigned int value)
{
	/*set reload value*/
	STK->RVR = value;
	/*enable interrupt*/
	STK->CSR |= (1U<<1);
	/*enable systick*/
	STK->CSR |= (1U<<0);
}

void start_systick(unsigned int value)
{
	/*set reload value*/
	STK->RVR = value;
	/*clear current value*/
	STK->CVR = 0;
	/*enable systick*/
	STK->CSR |= (1U<<0);
}

unsigned int get_state_systick(void)
{
	/* GET COUNTFLAG */
	return (STK->CSR) & (1U<<16);
}

void delay_ms_systick(unsigned int time_ms)
{
	while(time_ms--)
	{
		start_systick(0x1F3FU); /*1ms with fclk = 8Mhz*/
		while(0 == get_state_systick());
	}
}
