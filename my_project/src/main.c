
#include "hw_stm32f051r8.h"

/**********************************************************/
void Reserved_IRQHandler(void)
{
  while(1)
  {
  }
}

void NMI_Handler(void)
{
  while(1)
  {
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
  }
}

void SVC_Handler(void)
{
  while(1)
  {
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
  }
}

void EXTI2_3_IRQHandler(void)
{
	
	EXTI->PR |= (1U<<3);	//clear flag
}

/**********************************************************/

void delay(unsigned int timeout)
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

void NVIC_EnableIRQ(unsigned int IRQn)
{
	NVIC->ISER = 1<<(IRQn&0x1F);
}

void NVIC_DisableIRQn(unsigned int IRQn)
{
	NVIC->ICER = 1<<(IRQn&0x1F);
}



	//Pull PA.3 down internally, Trigger on rising edge
void main(void)
{
	RCC->AHBENR |= (1U<<17);	//Enable GPIOA Clock
	//GPIOA Mode 	00: input mode, 
	//				01: output mode, 
	//				10: alternate function mode,
	//				11: analog mode
	GPIOA->MODER &= (~3U)<<6;
	//GPIO Push-Pull: No pull up, pull down(00)
	//pull up(01), pull down(10), reserved(11)
	GPIOA->PUPDR &= (~3U)<<6;
	GPIOA->PUPDR |= (2U)<<6;
	NVIC_EnableIRQ(6);	//Enable Interrupt EXTI2_3
	RCC->APB2ENR |= 1;	//Enable SYSCFG Clock
	SYSCFG->EXTICR[0] &= (~7U)<<12;	//Connect GPIOA to EXTI3
	EXTI->IMR |= (1<<3);
	EXTI->RTSR |= (1<<3);
	while(1)
	{
	}
}


