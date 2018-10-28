#include "systick.h"

void systick_init(void)
{
	//SYSCLK not divided
	//RCC->CFGR &= ~(0x0F<<4);
	//SysTick counter enable, interrupt enable, clksourse: processor
	STK->CSR |= 0x07<<0;
	//Reaload value
	//0x7A1200(1s), 0x3D0900(0.5s), 
	//0xFD240(0.25s), 0x186A00(0.2s), 
	//0xC3500(0.1s)
	STK->RVR = 0x186A00;	
}