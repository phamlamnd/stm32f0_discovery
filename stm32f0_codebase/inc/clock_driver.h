#ifndef CLOCK_DRIVER_H
#define CLOCK_DRIVER_H

#include "hw_stm32f051r8.h"

typedef enum
{
    CLOCK_PORTA     = 0u,
    CLOCK_PORTB     = 1u,
    CLOCK_PORTC     = 2u,
    CLOCK_PORTD     = 3u,
    CLOCK_PORTE     = 4u,
} pripheral_clock_t;


void CLOCK_DRV_SystemInit();
void CLOCK_DRV_Config();
void CLOCK_DRV_Enable(pripheral_clock_t clock);
void CLOCK_DRV_Disable(pripheral_clock_t clock);
void delay(unsigned int timeout);

#endif /* CLOCK_DRIVER_H */
