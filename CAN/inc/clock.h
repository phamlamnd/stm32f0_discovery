#ifndef __CLOCK_H__
#define __CLOCK_H__
#include "hw_stm32f051r8.h"

void system_init(void);
void system_clock_config();
void clock_enable(void);
void delay(unsigned int timeout);

#endif /*__CLOCK_H__*/
