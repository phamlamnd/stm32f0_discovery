#include "gpio.h"

void gpio_init(void)
{
	/*Set LD3(PC9), MODER: output mode(01),OTYPER: push-pull(0), open-drain(1)*/
	GPIOC->MODER &= ~GPIO_MODER_MASK(LD3_PIN);
	GPIOC->MODER |= GPIO_MODER_OUTPUT(LD3_PIN);
	GPIOC->OTYPER &= ~GPIO_OTYPER_MASK(LD3_PIN);
	
	/*Set LD4(PC8), MODER: output mode(01),OTYPER: push-pull(0), open-drain(1)*/
	GPIOC->MODER &= ~GPIO_MODER_MASK(LD4_PIN);
	GPIOC->MODER |= GPIO_MODER_OUTPUT(LD4_PIN);
	GPIOC->OTYPER &= ~GPIO_OTYPER_MASK(LD4_PIN);
	
	/*Set PA0(USER_BUTTON), MODER: input mode(00),PUPDR: no pull-up, pull-down(00),pull up(01), pull-down(10)*/ 
	GPIOA->MODER &= ~GPIO_MODER_MASK(USER_BUTTON);
	GPIOA->PUPDR &= ~GPIO_PUPDR_MASK(USER_BUTTON);
	GPIOA->PUPDR |= GPIO_PUPDR_PULL_UP(USER_BUTTON);
	
	/*Set PA1, EXTI1 external iterrrupt*/
	GPIOA->MODER &= ~GPIO_MODER_MASK(1);
	GPIOA->PUPDR &= ~GPIO_PUPDR_MASK(1);
	GPIOA->PUPDR |= GPIO_PUPDR_PULL_UP(1);
	
	/*UART PIN: PA9 Alternate function mode, push-pull, no pull-up, no pull-down*/
	GPIOA->MODER &= ~GPIO_MODER_MASK(USART1_TX);			/*reset mode*/
	GPIOA->MODER |= GPIO_MODER_AF(USART1_TX);				/*AF mode*/
	GPIOA->OTYPER &= ~GPIO_OTYPER_MASK(USART1_TX);			/*push-pull*/
	GPIOA->PUPDR &= ~GPIO_PUPDR_MASK(USART1_TX);			/*no pull-up, no pull-down*/
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_HIGH_SPEED(USART1_TX);	/*high speed*/
	GPIOA->AFRH &= ~GPIO_AFRH_MASK(USART1_TX);				/*AF1*/
	GPIOA->AFRH |= GPIO_AFRH_AF1(USART1_TX);
	
	/*UART PIN: PA10 Alternate function mode, push-pull, no pull-up, no pull-down*/
	GPIOA->MODER &= ~GPIO_MODER_MASK(USART1_RX);			/*reset mode*/
	GPIOA->MODER |= GPIO_MODER_AF(USART1_RX);				/*AF mode*/
	GPIOA->OTYPER &= ~GPIO_OTYPER_MASK(USART1_RX);			/*push-pull*/
	GPIOA->PUPDR &= ~GPIO_PUPDR_MASK(USART1_RX);			/*no pull-up, no pull-down*/
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_HIGH_SPEED(USART1_RX);	/*high speed*/
	GPIOA->AFRH &= ~GPIO_AFRH_MASK(USART1_RX);				/*AF1*/
	GPIOA->AFRH |= GPIO_AFRH_AF1(USART1_RX);
}

void led_on(unsigned char pin_number)
{
	GPIOC->ODR |= 1U<<pin_number;
}

void led_off(unsigned char pin_number)
{
	GPIOC->ODR &= ~(1U<<pin_number);
}