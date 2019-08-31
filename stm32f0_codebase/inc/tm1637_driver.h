#ifndef TM1637_DRIVER_H
#define TM1637_DRIVER_H

#include "hw_stm32f051r8.h"
#include "gpio_driver.h"

typedef enum
{
    TM1637_COUNTER_MODE,        /* Display counter mode */
    TM1637_CLOCK_MODE           /* Display clock mode */
} tm1637_display_mode_t;

typedef struct
{
    unsigned char digit1;       /* Display number 0-9 */
    unsigned char digit2;       /* Display number 0-9 */
    unsigned char digit3;       /* Display number 0-9 */
    unsigned char digit4;       /* Display number 0-9 */
} tm1637_digit_t;

void TM1637_DRV_Config(tm1637_display_mode_t mode, tm1637_digit_t start);
void TM1637_DRV_Display(tm1637_digit_t digit);
void TM1637_DRV_Start();
void TM1637_DRV_Stop();


#endif /* TM1637_DRIVER_H */