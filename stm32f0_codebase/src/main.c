#include "clock_driver.h"
#include "gpio_driver.h"
#include "interrupt_manager.h"
#include "systick_driver.h"
#include "tm1637_driver.h"
#include "uart_driver.h"
#include "adc_driver.h"

void main(void)
{
    tm1637_digit_t digits = {
    .digit1 = 0,
    .digit2 = 0,
    .digit3 = 0,
    .digit4 = 0
    };
    gpio_config_t led4_config = {
        .pin    = 8,
        .mode   = GPIO_MODE_OUTPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    adc_cov_config_t conv_config;
    
    CLOCK_DRV_SystemInit();
    CLOCK_DRV_Enable(CLOCK_PORTC);
    CLOCK_DRV_Enable(CLOCK_ADC);
    GPIO_DRV_PinInit(GPIOC, &led4_config);
    
    TM1637_DRV_Config();
    
    ADC_DRV_EnableModule();
    ADC_DRV_GetDefaultConfigConverter(&conv_config);
    ADC_DRV_ConfigConverter(&conv_config);
    ADC_DRV_EnableChannel(17);
    
    delay(0x30);
    while(1)
    {
        ADC_DRV_StartConversion();
        delay(0x30);
        uint32_t result = (uint32_t)ADC_DRV_GetConversionResult(17);
        TM1637_DRV_Display(TM1637_COUNTER_MODE, digits);
        GPIO_DRV_TogglePin(GPIOC, PIN8);  
        delay(0x30);
        delay(0x30);
    }
}