#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "hw_stm32f051r8.h"

void GPIO_DRV_Init(void);
void led_on(unsigned char pin_number);
void led_off(unsigned char pin_number);

#endif /*GPIO_DRIVER_H*/
