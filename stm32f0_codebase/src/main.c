#include "clock_driver.h"
#include "gpio_driver.h"
#include "interrupt_manager.h"
#include "systick_driver.h"
#include "tm1637_driver.h"
#include "uart_driver.h"

void main(void)
{
    tm1637_digit_t digits = {
        .digit1 = 0,
        .digit2 = 0,
        .digit3 = 0,
        .digit4 = 0,
    };
    gpio_config_t led4_config = {
        .pin    = 8,
        .mode   = GPIO_MODE_OUTPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    CLOCK_DRV_SystemInit();
    CLOCK_DRV_Enable(CLOCK_PORTB);
    CLOCK_DRV_Enable(CLOCK_PORTC);
    GPIO_DRV_PinInit(GPIOC, &led4_config);
    TM1637_DRV_Config();
    while(1)
    {
        TM1637_DRV_Display(TM1637_COUNTER_MODE, digits);
        delay(0x30);
        delay(0x30);
        digits.digit1++;
        if(digits.digit1 == 10)
        {
            digits.digit1 = 0;
            digits.digit2++;
        }
        if(digits.digit2 == 6)
        {
            digits.digit2 = 0;
            digits.digit3++;
        }
        if(digits.digit3 == 10)
        {
            digits.digit3 = 0;
            digits.digit4++;
        }
        if(digits.digit3 == 3 && digits.digit4 == 1)
        {
            digits.digit3 = 0;
            digits.digit4 = 0;
        }
        GPIO_DRV_TogglePin(GPIOC, PIN8);
        TM1637_DRV_Display(TM1637_CLOCK_MODE, digits);
        delay(0x30);
        delay(0x30);
    }
}