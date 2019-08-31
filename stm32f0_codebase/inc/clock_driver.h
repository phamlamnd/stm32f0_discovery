#ifndef CLOCK_DRIVER_H
#define CLOCK_DRIVER_H

#include "hw_stm32f051r8.h"

void CLOCK_DRV_Init();
void CLOCK_DRV_Config();
void CLOCK_DRV_Enable();
void delay(unsigned int timeout);

#endif /* CLOCK_DRIVER_H */
