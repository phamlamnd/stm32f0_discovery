
#include "hw_stm32f051r8.h"

void led_on(unsigned char pin_number);
void led_off(unsigned char pin_number);

/**********************************************************/
void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}


void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void EXTI0_1_IRQHandler(void)
{
	static unsigned char flag = 0;
	if(0 == flag)
	{
		led_on(LD3_PIN);
		flag = 1;
	}
	else
	{
		led_off(LD3_PIN);
		flag = 0;
	}
	NVIC->ICPR |= 1U<<5;
	EXTI->PR |= 1U<<0;
}

/**********************************************************/

void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFF; t2++)
        {
          asm(" nop");
        }
    }
}

void enable_clk(void)
{
	/*Enable clock for Port C*/
	RCC->AHBENR |= GPIOC_CLOCK_EN;
	/*Enable clock for Port A*/
	RCC->AHBENR |= GPIOA_CLOCK_EN;
	/*Enable clock for SYSCFG*/
	RCC->APB2ENR |= SYSCFG_CLOCK_EN;
}

void init_pin(void)
{
	/*Init Pin LD3_PIN*/
	GPIOC->MODER &= ~GPIO_MODER_MASK(LD3_PIN);
	GPIOC->MODER |= GPIO_MODER_OUTPUT(LD3_PIN);
	/*Init Pin LD4_PIN*/
	GPIOC->MODER &= ~GPIO_MODER_MASK(LD4_PIN);
	GPIOC->MODER |= GPIO_MODER_OUTPUT(LD4_PIN);
	/*Init USER_BUTTON (PA0)*/
	GPIOA->MODER &= ~GPIO_MODER_MASK(USER_BUTTON);
	GPIOA->MODER |= GPIO_MODER_INPUT(USER_BUTTON);
	GPIOA->PUPDR &= GPIO_PUPDR_MASK(USER_BUTTON);
	GPIOA->PUPDR |= GPIO_PUPDR_PULL_UP(USER_BUTTON);
}

void init_interrupt(void)
{
	/*SYSCFG*/
	SYSCFG->EXTICR1 &= ~SYSCFG_EXTICR1_EXTI_MASK(0);
	SYSCFG->EXTICR1 |= SYSCFG_EXTICR1_EXTI_PA(0);
	/*EXTI*/
	EXTI->IMR |= EXTI_IMR(0);
	EXTI->RTSR |= EXTI_RTSR_EN(0);
	/*NVIC*/
	NVIC->ISER |= 1U<<5;
	/*enable global interrupt*/
	asm("cpsie i");
}

void led_on(unsigned char pin_number)
{
	//GPIOC->BSRR |= GPIO_BSRR_BS(pin_number);
	GPIOC->ODR |= GPIO_ODR(pin_number);
}

void led_off(unsigned char pin_number)
{
	//GPIOC->BSRR |= GPIO_BSRR_BR(pin_number);
	GPIOC->ODR &= ~GPIO_ODR(pin_number);
}

void main(void)
{
	enable_clk();
	init_pin();
	init_interrupt();
	while(1)
	{
		led_on(LD4_PIN);
		delay(0xff);
		led_off(LD4_PIN);
		delay(0xff);
	}
}




