#include "clock_driver.h"
#include "gpio_driver.h"
#include "interrupt_manager.h"
#include "systick_driver.h"
#include "tm1637_driver.h"
#include "uart_driver.h"

void main(void)
{
    tm1637_digit_t config = {
        .digit1 = 0,
        .digit2 = 0,
        .digit3 = 0,
        .digit4 = 0,
    };
    unsigned char donvi = 0;
    unsigned char tram = 0;
    unsigned char chuc = 0; 
    unsigned char ngan = 0;
    gpio_config_t config1 = {
        .pin    = 8,
        .mode   = GPIO_MODE_OUTPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    CLOCK_DRV_Init();
    CLOCK_DRV_Config();
    CLOCK_DRV_Enable();
    GPIO_DRV_PinInit(GPIOA, &config1);
    TM1637_DRV_Config(TM1637_CLOCK_MODE, config);
    while(1)
    {
        TM1637_DRV_Display(config);
        delay(0x5);

        donvi++;
        if(donvi == 10)
        {
            donvi = 0;
            chuc = chuc+1;
        }
        if(chuc == 10)
        {
            chuc = 0;
            tram = tram+1;
        }
        if(tram == 10)
        {
            tram = 0;
            ngan = ngan+1;
        }
        if(ngan == 10)
        {
            ngan = 0;
        }
        config.digit1 = donvi;
        config.digit2 = chuc;
        config.digit3 = tram;
        config.digit4 = ngan;
        TM1637_DRV_Display(config);
        delay(0x5);
    }
}