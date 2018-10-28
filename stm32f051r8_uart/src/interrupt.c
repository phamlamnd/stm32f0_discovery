#include "interrupt.h"
#include "gpio.h"
#include "usart.h"

volatile unsigned char rx_data = 0;

void Reserved_IRQHandler()
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler()
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler()
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler()
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler()
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler()
{
	GPIOC->ODR ^= (1U<<LD4_PIN);		//Togge LED3
}

void EXTI0_1_IRQHandler()
{
	GPIOC->ODR ^= (1U<<LD3_PIN);	//Togge LED3
	EXTI->PR = (1U<<1);				//Clear Pending interrupt flag on line 1
	NVIC->ICPR = (1U<<5);			//Clear interrupt 5
}

void EXTI2_3_IRQHandler()
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void USART1_IRQHandler()
{	
    if (0 != (USART1->ISR & (1U<<6))) /* Tx - TC flag */
    {
        USART1->ICR = (1U<<6);
    }

    if (0 != (USART1->ISR & (1U<<5)))  /* Rx - RXNE flag */
    {
        rx_data = USART1->RDR & 0x000000FFU;
        USART1->RQR |= (1U<<3); /* ghi giá trị 1 tới USART_RQR[RXFRQ] để xóa cờ USART_ISR[RXNE] */
    }
}

void NVIC_EnableIRQ(unsigned int IRQn)
{
	NVIC->ISER = (1U<<IRQn);
}

void NVIC_DisableIRQ(unsigned int IRQn)
{
	NVIC->ICER = (1U<<IRQn);
}

void NVIC_SetPriority(unsigned int IRQn, unsigned int priority)
{
	NVIC->IPR[IRQn>>2] &= ~3U<<(8*(IRQn&0x3U) + 6);
	NVIC->IPR[IRQn>>2] |= priority<<(8*(IRQn&0x3U) + 6);
}
 

void interrupt_init()
{
	/*EXTI1*/
	/*Select the source input for the EXTI1 interrupt is PA1 for Line 1*/
	SYSCFG->EXTICR1 &= ~SYSCFG_EXTICR1_EXTI_MASK(1);
	/*Interrupt request from Line 1 is not masked*/
	EXTI->IMR |= EXTI_IMR_NOT_MASK(1);
	/*Rising trigger event configuration bit of Line 1*/
	EXTI->RTSR |= EXTI_RTSR_EN(1);
	/*Enable EXTI Line 1 Interrupt*/
	NVIC_EnableIRQ(5);
	/*Set priority*/
	NVIC_SetPriority(5, 1);
	
	/*USART1*/
	/*Clear Flag*/
	USART1->ICR |= (0xFFFFFFFFU);
	USART1->RQR |= (0xFFFFFFFFU);
	/*RXNE interrupt enable*/
	USART1->CR1 |= (1U<<5);		//RXNEIE = 1
	/*Transmission complete interrupt enable*/
	USART1->CR1 |= (1U<<6);		//TCIE = 1
	/*Enable USART1 global interrupt*/
	NVIC->ISER |= (1U<<27);
	/*Set priority*/
	NVIC_SetPriority(27, 1);
	
	asm("cpsie i");
}