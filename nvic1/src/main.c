
#include "hw_stm32f051r8.h"
unsigned int led_state = 0;
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
	unsigned int temp;
	/*Ngat PA0*/
	temp = read_reg(EXTI_PR, (0x01 << 0));
	
	if(temp == 0x01u)
	{
		if(led_state == 0)
		{
			led_on(LD3_PIN);
			led_state = 1;
		}
		else
		{
			led_off(LD3_PIN);
			led_state = 0;
		}
	}
	
	/*xoa co ngat*/
	temp = 1<<0;
	write_reg(EXTI_PR, temp);
	/*xoa co ngat NVIC*/
	write_reg(NVIC_ICPR, 1<<5);
	
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

void enable_clk(void)
{
	unsigned int temreg;
	
	temreg = read_reg(RCC_AHBENR, ~(0x01 << 19));
	temreg = temreg | 0x01 << 19;
	write_reg(RCC_AHBENR, temreg);
	
	temreg = read_reg(RCC_AHBENR, ~(0x01 << 17));
	temreg = temreg | 0x01 << 17;
	write_reg( RCC_AHBENR, temreg);
}

void init_pin(void)
{
	unsigned int temreg;
	temreg = read_reg(GPIOC_MODER, ~(0x03 << 18));
	temreg = temreg | GPIOC_MODER_OUTPUT << 18;
	write_reg(GPIOC_MODER, temreg);
	
	temreg = read_reg(GPIOC_MODER, ~(0x03 << 16));
	temreg = temreg | GPIOC_MODER_OUTPUT << 16;
	write_reg(GPIOC_MODER, temreg);
	
	temreg = read_reg(GPIOA_MODER, ~(0x03 << 0));
	temreg = temreg | GPIOA_MODER_INPUT << 0;
	write_reg(GPIOA_MODER, temreg);
}

void init_interrupt(void)
{
	unsigned int temreg;
	/*enable interrupt for EXTI0*/
	temreg = read_reg(EXTI_IMR, ~(0x01 << 0));
	temreg = temreg | 0x01 << 0;
	write_reg(EXTI_IMR, temreg);
	
	temreg = read_reg(EXTI_RTSR, ~(0x1u << 0));
	temreg = temreg | 0x1u << 0;
	write_reg(EXTI_RTSR, temreg);
	/*SYSCFG*/
	temreg = read_reg(SYSCFG_EXTICR1, ~(0x0Fu << 0));
	temreg = temreg | 0x00u << 0;
	write_reg(SYSCFG_EXTICR1, temreg);
	/*NVIC*/
	temreg = read_reg(NVIC_PRI1, ~(0xFFu << 8));
	temreg = temreg | 0x01u << 14;
	write_reg(NVIC_PRI1, temreg);
	
	temreg = read_reg(NVIC_ISER, ~(0x1u << 5));
	temreg = temreg | 0x01u << 5;
	write_reg(NVIC_ISER, temreg);
	/*enable global interrupt*/
	asm("cpsie i");
}

void led_on(unsigned char pin_number)
{
	write_reg(GPIOC_BSRR, 0x01 << pin_number);
}

void led_off(unsigned char pin_number)
{
	write_reg(GPIOC_BSRR, 0x01 << (pin_number + 16u));
}

void main(void)
{

	enable_clk();
	init_pin();
	init_interrupt();
	while(1)
	{
		
	}
}




