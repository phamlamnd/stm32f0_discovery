#include "gpio_driver.h"

void GPIO_DRV_PinInit(GPIO_TypeDef* const gpio, const gpio_config_t* const config)
{
    uint32_t pin_number = config->pin;
    if(config->mode == GPIO_MODE_INPUT)
    {
        REG_BIT_CLEAR32(&(gpio->MODER), (GPIO_MODER_MODER_MASK << (GPIO_MODER_MODER_WITH * pin_number)));
        REG_BIT_CLEAR32(&(gpio->PUPDR), (GPIO_PUPDR_PUPDR_MASK << (GPIO_PUPDR_PUPDR_WITH * pin_number)));
        REG_BIT_SET32(&(gpio->PUPDR), (config->pull << (GPIO_PUPDR_PUPDR_WITH * pin_number)));
    }
    else if(config->mode == GPIO_MODE_OUTPUT)
    {
        REG_BIT_CLEAR32(&(gpio->MODER), (GPIO_MODER_MODER_MASK << (GPIO_MODER_MODER_WITH * pin_number)));
        REG_BIT_SET32(&(gpio->MODER), GPIO_MODE_OUTPUT << (GPIO_MODER_MODER_WITH * pin_number));
            /* Config output type push pull / open drain */
        REG_BIT_CLEAR32(&(gpio->OTYPER), (GPIO_OTYPER_OT_MASK << (GPIO_OTYPER_OT_WITH * pin_number)));
        REG_BIT_SET32(&(gpio->OTYPER), (config->type << (GPIO_OTYPER_OT_WITH * pin_number)));
        /* Config output speed mode */
        REG_BIT_CLEAR32(&(gpio->OSPEEDR), (GPIO_OSPEEDR_OSPEEDR_MASK << (GPIO_OSPEEDR_OSPEEDR_WITH * pin_number)));
        REG_BIT_SET32(&(gpio->OSPEEDR), (config->speed << (GPIO_OSPEEDR_OSPEEDR_WITH * pin_number)));
    }
    else
    {
        
    }
}

void GPIO_DRV_SetPin(GPIO_TypeDef* const gpio, const uint32_t pin)
{
    REG_BIT_SET32(&(gpio->ODR), (1U << pin));
}

void GPIO_DRV_ClearPin(GPIO_TypeDef* const gpio, const uint32_t pin)
{
    REG_BIT_CLEAR32(&(gpio->ODR), (1U << pin));
}

void GPIO_DRV_TogglePin(GPIO_TypeDef* const gpio, const uint32_t pin)
{
    gpio->ODR ^= (1U << pin);
}