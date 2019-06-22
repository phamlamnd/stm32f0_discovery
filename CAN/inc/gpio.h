#ifndef __GPIO_H__
#define __GPIO_H__
#include "hw_stm32f051r8.h"

void gpio_init(void);
void led_on(unsigned char pin_number);
void led_off(unsigned char pin_number);

#endif /*__GPIO_H__*/
