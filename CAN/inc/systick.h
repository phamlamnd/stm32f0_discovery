#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "hw_stm32f051r8.h"

void systick_init(void);
void systick_interrupt_enable(unsigned int value);
void start_systick(unsigned int value);
unsigned int get_state_systick(void);
void delay_ms_systick(unsigned int time_ms);

#endif /*__SYSTICK_H__*/