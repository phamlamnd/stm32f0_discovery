
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__

#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

/*GPIOA*/
#define BASE_ADDR_GPIOA		0x48000000u
#define GPIOA_MODER			(BASE_ADDR_GPIOA + 0x0)
#define GPIOA_MODER_INPUT	0x00u
#define GPIOA_MODER_OUTPUT	0x01u
#define GPIOA_MODER_ALT		0x02u
#define GPIOA_IDR			(BASE_ADDR_GPIOA + 0x10u)
#define GPIOA_BSRR			(BASE_ADDR_GPIOA + 0x18u)


/*GPIOC*/
#define BASE_ADDR_GPIOC		0x48000800u
#define GPIOC_MODER			(BASE_ADDR_GPIOC + 0x00u)
#define GPIOC_MODER_INPUT	0x00u
#define GPIOC_MODER_OUTPUT	0x01u
#define GPIOC_MODER_ALT		0x02u
#define GPIOC_BSRR			(BASE_ADDR_GPIOC + 0x18u)

/*LED PIN and BUTTON*/
#define LD3_PIN				9
#define USER_BUTTON			0

/*RCC-CLOCK*/
#define BASE_ADDR_RCC		0x40021000u
#define RCC_AHBENR			(BASE_ADDR_RCC + 0x14u)


/*
#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

#define BASE_ADDRESS_GPIOA        0x48000000u

#define LED_D2_PIN_MODE           0x00000100u
#define LED_D2_OFF                0x00000010u
#define LED_D2_ON                 0x00000000u


#define GPIOA_MODER               BASE_ADDRESS_GPIOA + 0x00
#define GPIOA_IDR                 BASE_ADDRESS_GPIOA + 0x10
#define GPIOA_ODR                 BASE_ADDRESS_GPIOA + 0x14
#define GPIOA_BSRR                BASE_ADDRESS_GPIOA + 0x18

#define BASE_ADDRESS_RCC          0x40021000u

#define RCC_AHBENR                BASE_ADDRESS_RCC + 0x14
#define RCC_AHBENR_IOPAEN         0x00020000u

#define enabled_clk()       do { \
                              unsigned long int tmpreg; \
                              tmpreg = read_reg(RCC_AHBENR, ~RCC_AHBENR_IOPAEN);\
                              tmpreg = tmpreg | RCC_AHBENR_IOPAEN; \
                              write_reg(RCC_AHBENR, tmpreg);\
                              delay(10); \
                            } while(0U)

#define init_led_pin()      do { \
                              unsigned long int tmpreg; \
                              tmpreg = read_reg(GPIOA_MODER, 0xFFFFFCFF); \
                              tmpreg = tmpreg | LED_D2_PIN_MODE; \
                              write_reg(GPIOA_MODER, tmpreg); \
                            } while(0U)

#define led_on()            write_reg(GPIOA_ODR, LED_D2_ON);

#define led_off()           write_reg(GPIOA_ODR, LED_D2_OFF);

/* end file */
#endif /* __HW_STM32F051R8_H__ */

