#include "interrupt.h"
#include "gpio.h"
#include "usart.h"

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
	GPIOC->ODR ^= 0x01<<8;
}

void EXTI0_1_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void EXTI2_3_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void USART1_IRQHandler(void)
{
	
}

void interrupt_init(void)
{
	
}