#include "hw_stm32f051r8.h"

void Led_On(unsigned char pin_number)
{
	//GPIOC->BSRR |= 0x01<<pin_number;
	GPIOC->ODR |= 0x01<<pin_number;
}

void Led_Off(unsigned char pin_number)
{
	//GPIOC->BSRR |= 0x01<<(pin_number+16);
	//GPIOC->ODR &= ~(0x01<<pin_number);
	GPIOC->BRR |= 0x01<<pin_number;
}

void Delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm(" nop");
        }
    }
}

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
	if(EXTI->PR & (0x01<<0)) //If interrupt PIN0
	{
		Led_On(LD3_PIN);
	}
	else if(EXTI->PR & (0x01<<1)) //If interrupt PIN1
	{		
		Led_Off(LD3_PIN);
	}
	else{}
	//Clear Pending Flag Line 0 and Line 1
	EXTI->PR |= 0x01<<0;
	EXTI->PR |= 0x01<<1;
	//Clear pending in NVIC
	NVIC->ICPR |= 0x01<<5;
}

void EXTI2_3_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<2)) //If interrupt PIN2
	{
		Led_Off(LD3_PIN);
	}
	else if(EXTI->PR & (0x01<<3)) //If interrupt PIN3
	{		
		Led_On(LD3_PIN);
	}
	else{}
	//Clear Pending Flag Line 2 and Line 3
	EXTI->PR |= 0x01<<2;
	EXTI->PR |= 0x01<<3;
	//Clear pending in NVIC
	NVIC->ICPR |= 0x01<<6;
}

void EXTI4_15_IRQHandler(void)
{
	//Clear Pending Flag Line 4
	EXTI->PR |= 0x01<<4;
	//Clear pending in NVIC
	NVIC->ICPR |= 0x01<<7; 
}	

/**********************************************************/

void Enable_Clk(void)
{
	//HSI ON by default
	RCC->CR |= 0x01<<0;
	
	//Enable clock GPIOA
	RCC->AHBENR |= 0x01<<17;
	
	//Enable clock GPIOB
	RCC->AHBENR |= 0x01<<18;
	
	//Enable clock GPIOC
	RCC->AHBENR |= 0x01<<19;
	
	//Enable clock SYSCFG
	RCC->APB2ENR |= 0x01<<0;
	
}

void Init_Pin(void)
{
	//Set LD3(PC9), MODER: output mode(01),
	//OTYPER: push-pull(0), open-drain(1),
	GPIOC->MODER &= ~(0x03<<18);
	GPIOC->MODER |= 0x01<<18;
	GPIOC->OTYPER &= ~(0x01<<9);
	
	//Set LD4(PC8), MODER: output mode(01),
	//OTYPER: push-pull(0), open-drain(1),
	GPIOC->MODER &= ~(0x03<<16);
	GPIOC->MODER |= 0x01<<16;
	GPIOC->OTYPER &= ~(0x01<<8);
	
	//Set PA0(USER_BUTTON), MODER: input mode(00),
	//PUPDR: no pull-up, pull-down(00),pull up(01), pull-down(10) 
	GPIOA->MODER &= ~(0x03<<0);
	GPIOA->PUPDR &= ~(0x03<<0);
	GPIOA->PUPDR |= 0x01<<0;
	
	//Set PA2: exti: input mode(00), pull up(01)
	GPIOA->MODER &= ~(0x03<<4);
	GPIOA->PUPDR &= ~(0x03<<4);
	GPIOA->PUPDR |= 0x01<<4;
	
	//Set PA1: exti: input mode(00), pull up(01)
	GPIOA->MODER &= ~(0x03<<2);
	GPIOA->PUPDR &= ~(0x03<<2);
	GPIOA->PUPDR |= 0x01<<2;
	
	//Set PA3: exti: input mode(00), pull up(01)
	GPIOA->MODER &= ~(0x03<<6);
	GPIOA->PUPDR &= ~(0x03<<6);
	GPIOA->PUPDR |= 0x01<<6;
}

void Init_Interrupt(void)
{
	/*Config for EXTI0*/
	//Connect LINE 0 to PA0
	SYSCFG->EXTICR[0] &= ~(0x0F<<0);
	//EXTI0 not mask
	EXTI->IMR |= 0x01<<0;
	//Rising trigger selection
	EXTI->RTSR |= 0x01<<0;
	//NVIC
	NVIC->ISER |= 0x01<<5;
	NVIC->IPR[1] &= ~(0x03<<14);
	NVIC->IPR[1] |= 0x01<<14;
	
	/*Config for EXTI2*/
	//Connect LINE 2 to PA2
	SYSCFG->EXTICR[0] &= ~(0x0F<<8);
	//EXTI2 not mask
	EXTI->IMR |= 0x01<<2;
	//Rising trigger selection
	EXTI->RTSR |= 0x01<<2;
	//NIVC
	NVIC->ISER |= 0x01<<6;
	NVIC->IPR[1] &= ~(0x03<<22);
	NVIC->IPR[1] |= 0x02<<22;
	
	/*Config for EXTI1*/
	//Connect LINE 1 to PA1
	SYSCFG->EXTICR[0] &= ~(0x0F<<4);
	//EXTI1 not mask
	EXTI->IMR |= 0x01<<1;
	//Rising trigger selection
	EXTI->RTSR |= 0x01<<1;
	//NIVC
	NVIC->ISER |= 0x01<<5;
	NVIC->IPR[1] &= ~(0x03<<14);
	NVIC->IPR[1] |= 0x01<<14;
	
	
	/*Config for EXTI3*/
	//Connect LINE 3 to PA3
	SYSCFG->EXTICR[0] &= ~(0x0F<<12);
	//EXTI1 not mask
	EXTI->IMR |= 0x01<<3;
	//Rising trigger selection
	EXTI->RTSR |= 0x01<<3;
	//NIVC
	NVIC->ISER |= 0x01<<6;
	NVIC->IPR[1] &= ~(0x03<<22);
	NVIC->IPR[1] |= 0x02<<22;
}


void main(void)
{
	Enable_Clk();
	Init_Pin();
	//Init_Interrupt();
	while(1)
	{
		//Led_On(LD4_PIN);
		Delay(0xE);
		//Led_Off(LD4_PIN);
		//Delay(0xE);
		GPIOC->ODR ^= (0x01<<8);
		Delay(0xE);
		GPIOC->ODR ^= (0x01<<9);
	}
}