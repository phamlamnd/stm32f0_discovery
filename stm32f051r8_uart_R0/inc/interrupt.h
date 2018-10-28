#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "hw_stm32f051r8.h"

volatile unsigned char rx_data;

void Reserved_IRQHandler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void USART1_IRQHandler(void);
void interrupt_init(void);

#endif /*__INTERRUPT_H__*/
