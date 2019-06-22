
#include "hw_stm32f051r8.h"

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
	unsigned char flag = 0;
	while(1)
	{
		if((GPIOA->IDR & GPIO_IDR_MASK(USER_BUTTON)) == GPIO_IDR_MASK(USER_BUTTON))
		{
			if(0 == flag)
			{
				flag = 1;
			}
			else
			{
				flag = 0;
			}	
		}
		
		if(0 == flag)
		{
			led_off(LD3_PIN);
			led_on(LD4_PIN);
			delay(0xf0);
			led_off(LD4_PIN);
			delay(0xf0);
		}
		else if(1 == flag)
		{
			led_off(LD4_PIN);
			led_on(LD3_PIN);
			delay(0xf0);
			led_off(LD3_PIN);
			delay(0xf0);
		}
		delay(0xf0);
	}
}




