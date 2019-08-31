#include "gpio_driver.h"

void GPIO_DRV_PinInit(GPIO_TypeDef* const gpio,
                      const gpio_config_t* const config)
{
    if(gpio == NULL){
        return;
    }
    /* Get pin number */
    uint32_t pin_number = config->pin;
    /* Config input/output mode */
    REG_BIT_CLEAR32(&(gpio->MODER), (GPIO_MODER_MODER_MASK << (GPIO_MODER_MODER_WITH * pin_number)));
    REG_WRITE32(&(gpio->MODER), (config->mode << (GPIO_MODER_MODER_WITH * pin_number)));
    /* Config output type push pull / open drain */
    REG_BIT_CLEAR32(&(gpio->OTYPER), (GPIO_OTYPER_OT_MASK << pin_number));
    REG_WRITE32(&(gpio->OTYPER), (config->type << (GPIO_OTYPER_OT_WITH * pin_number)));
    
    REG_BIT_CLEAR32(&(gpio->OSPEEDR), GPIO_OSPEEDR_OSPEEDR_MASK << (GPIO_OSPEEDR_OSPEEDR_WITH * pin_number));
    REG_WRITE32(&(gpio->OSPEEDR), (config->speed << (GPIO_OSPEEDR_OSPEEDR_WITH * pin_number)));
    
    REG_BIT_CLEAR32(&(gpio->PUPDR), GPIO_PUPDR_PUPDR_MASK << (GPIO_PUPDR_PUPDR_WITH * pin_number));
    REG_WRITE32(&(gpio->PUPDR), (config->pull << (GPIO_PUPDR_PUPDR_WITH * pin_number)));
    
    /*Set LD3(PC9), MODER: output mode(01),OTYPER: push-pull(0), open-drain(1)*/
    GPIOC->MODER &= ~(0x03<<18);
    GPIOC->MODER |= 0x01<<18;
    GPIOC->OTYPER &= ~(0x01<<9);

    /*Set LD4(PC8), MODER: output mode(01),OTYPER: push-pull(0), open-drain(1)*/
    GPIOC->MODER &= ~(0x03<<16);
    GPIOC->MODER |= 0x01<<16;
    GPIOC->OTYPER &= ~(0x01<<8);

    /*Set PA0(USER_BUTTON), MODER: input mode(00),PUPDR: no pull-up, pull-down(00),pull up(01), pull-down(10)*/
    GPIOA->MODER &= ~(0x03<<0);
    GPIOA->PUPDR &= ~(0x03<<0);
    GPIOA->PUPDR |= 0x01<<0;

    /*UART PIN: PA9 Alternate function mode, push-pull, no pull-up, no pull-down*/
    GPIOA->MODER &= ~(0x03<<18);	/*reset mode*/
    GPIOA->MODER |= 0x02<<18;		/*AF mode*/
    GPIOA->OTYPER &= ~(0x01<<9);	/*push-pull*/
    GPIOA->PUPDR &= ~(0x03<<18);	/*no pull-up, no pull-down*/
    GPIOA->OSPEEDR |= 0x03<<18;		/*high speed*/
    GPIOA->AFRH &= ~(0xF<<4);		/*AF1*/
    GPIOA->AFRH |= 0x01<<4;

    /*UART PIN: PA10 Alternate function mode, push-pull, no pull-up, no pull-down*/
    GPIOA->MODER &= ~(0x03<<20);    /*reset mode*/
    GPIOA->MODER |= 0x02<<20;       /*AF mode*/
    GPIOA->OTYPER &= ~(0x01<<10);   /*push-pull*/
    GPIOA->PUPDR &= ~(0x03<<20);    /*no pull-up, no pull-down*/
    GPIOA->OSPEEDR |= 0x03<<20;    /*high speed*/
    GPIOA->AFRH &= ~(0xF<<9);       /*AF1*/
    GPIOA->AFRH |= 0x01<<9;
}

void led_on(unsigned char pin_number)
{
    GPIOC->ODR |= 0x01<<pin_number;
}

void led_off(unsigned char pin_number)
{
    GPIOC->ODR &= ~(0x01<<pin_number);
}