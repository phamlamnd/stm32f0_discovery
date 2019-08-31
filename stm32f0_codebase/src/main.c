#include "clock_driver.h"
#include "gpio_driver.h"
#include "interrupt_manager.h"
#include "systick_driver.h"
#include "tm1637_driver.h"
#include "uart_driver.h"

void main(void)
{
    unsigned int donvi = 0;
    unsigned int chuc = 0;
    unsigned int tram = 0;
    unsigned int ngan = 0;
    CLOCK_DRV_Init();
    CLOCK_DRV_Config();
    CLOCK_DRV_Enable();
    GPIO_DRV_Init();
    TM1637_DRV_Init();
    while(1)
    {
        TM1637_DRV_Display(ngan, tram, chuc, donvi);
        delay(0x2);

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

        TM1637_DRV_Display(ngan, tram, chuc, donvi);
        delay(0x2);
    }
}