#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "hw_stm32f051r8.h"

typedef enum
{
    GPIO_INPUT_MODE     = 0U,
    GPIO_OUTPUT_MODE    = 1U,
    GPIO_FUNCTION_MODE  = 2U,
    GPIO_ANALOG_MODE    = 3U
} gpio_mode_t;

void GPIO_DRV_Init();
void led_on(unsigned char pin_number);
void led_off(unsigned char pin_number);

#endif /*GPIO_DRIVER_H*/
