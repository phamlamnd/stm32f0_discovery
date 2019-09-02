#include "clock_driver.h"
#include "gpio_driver.h"
#include "interrupt_manager.h"
#include "systick_driver.h"
#include "tm1637_driver.h"
#include "uart_driver.h"
#include "adc_driver.h"

int main(void)
{
    gpio_config_t led4_config0 = {
        .pin    = 8,
        .mode   = GPIO_MODE_OUTPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    gpio_config_t analog_pin_config0 = {
        .pin    = 0,
        .mode   = GPIO_MODE_ANALOG,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_NO
    };
    
    adc_cov_config_t conv_config0 = {
        .convMode   = ADC_CONTINUOUS_CONV_MODE,
        .resolution = ADC_DATA_RESOLUTION_12BITS,  
        .overwrite  = ADC_DATA_OVERWRITTEN,
        .align      = ADC_DATA_RIGHT_ALIGNED,
        .edge       = ADC_HARDWARE_TRIGGER_DISABLE,
        .clock      = ADC_CLOCK_CLK_MODE,
        .sample     = ADC_SAMPLE_TIME_28_5_CLOCK_CYCLES,
        .scan       = ADC_SCAN_BACKWARD,
    };
    
    tm1637_digit_t digits = {
        .digit1 = 1,
        .digit2 = 0,
        .digit3 = 0,
        .digit4 = 0
    };
    
    CLOCK_DRV_SystemInit();
    CLOCK_DRV_Enable(CLOCK_PORTA);
    CLOCK_DRV_Enable(CLOCK_PORTC);
    CLOCK_DRV_Enable(CLOCK_ADC);
    GPIO_DRV_PinInit(GPIOC, &led4_config0);
    GPIO_DRV_PinInit(GPIOA, &analog_pin_config0);
    TM1637_DRV_Config();
    ADC_DRV_DoCalibaration();
    ADC_DRV_EnableModule();
    ADC_DRV_ConfigConverter(&conv_config0);
    ADC_DRV_EnableChannel(0);
    ADC_DRV_StartConversion();
    
    while(1)
    {
        
        uint32_t flags = ADC_DRV_GetStatusFlags();
        if((flags & ADC_ISR_EOC_MASK) != 0)
        {
            uint16_t result = ADC_DRV_GetConversionResult();
            ADC_DRV_ClearStatusFlags(ADC_ISR_EOC_MASK);
            digits.digit1++;
            if(digits.digit1 == 10)
            {
                digits.digit1 = 0;
            }
        }
        TM1637_DRV_Display(TM1637_COUNTER_MODE, digits);
        GPIO_DRV_TogglePin(GPIOC, PIN8);
        delay(0x30);
    }
}