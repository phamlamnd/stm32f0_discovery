
#include "hw_stm32f051r8.h"
unsigned int led_state = 1;
/**********************************************************/
void led_on(unsigned char pin_number)
{
	write_reg(GPIOC_BSRR, 0x01 << pin_number);
}

void led_off(unsigned char pin_number)
{
	write_reg(GPIOC_BSRR, 0x01 << (pin_number + 16u));
}

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
	temp = read_reg(EXTI_PR, (1<<0));
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
	
	/*Xoa co ngat cua ngoai vi*/
	temp = 1<<0;
	write_reg(EXTI_PR, temp);
	//EXTI_PR |= 0x01<<0;
	
	/*Xoa co ngat cua NVIC*/
	write_reg(NVIC_ICPR, 1<<5);
	
}


void EXTI2_3_IRQHandler(void)
{
	unsigned int temp;
	delay(0xfff);
	temp = 1<<2;
	write_reg(EXTI_PR, temp);
	
	/*Xoa co ngat cua NVIC*/
	write_reg(NVIC_ICPR, 1<<6);
}


/**********************************************************/


void enable_clk(void)
{
	unsigned int temreg;
	
	temreg = read_reg(RCC_AHBENR, ~(0x01 << 19));
	temreg = temreg | 0x01 << 19;
	write_reg(RCC_AHBENR, temreg);
	
	temreg = read_reg(RCC_AHBENR, ~(0x01 << 17));
	temreg = temreg | 0x01 << 17;
	write_reg(RCC_AHBENR, temreg);
}

void init_pin(void)
{
	unsigned int temreg;
	//Set Mode LD3
	temreg = read_reg(GPIOC_MODER, ~(0x03 << 18));
	temreg = temreg | GPIOC_MODER_OUTPUT << 18;
	write_reg(GPIOC_MODER, temreg);
	
	//Set Mode LD4
	temreg = read_reg(GPIOC_MODER, ~(0x03 << 16));
	temreg = temreg | GPIOC_MODER_INPUT << 16;
	write_reg(GPIOC_MODER, temreg);
	
	//Set Mode Button
	temreg = read_reg(GPIOA_MODER, ~(0x03 << 0));
	temreg = temreg | GPIOA_MODER_INPUT << 0;
	write_reg(GPIOA_MODER, temreg);
	
	//Set Mode PA2
	temreg = read_reg(GPIOA_MODER, ~(0x03 << 4));
	temreg = temreg | GPIOA_MODER_INPUT << 4;
	write_reg(GPIOA_MODER, temreg);
	
	//
	temreg = read_reg(GPIOA_PUPDR, ~(0x03 << 4));
	temreg = temreg | (0x01 << 4);
	write_reg(GPIOA_PUPDR, temreg);
}

void init_interrupt(void)
{
	unsigned int temreg;
	/*Enable interrupt for EXTI0*/
	temreg = read_reg(EXTI_IMR, ~(0x01u << 0));
	temreg = temreg | (0x01u << 0);
	write_reg(GPIOC_MODER, temreg);
	
	temreg = read_reg(EXTI_RTSR, ~(0x01u << 0));
	temreg = temreg | (0x01u << 0);
	write_reg(EXTI_RTSR, temreg);
	
	/*Enable interrupt for EXTI2*/
	temreg = read_reg(EXTI_IMR, ~(0x01u << 2));
	temreg = temreg | (0x01u << 2);
	write_reg(GPIOC_MODER, temreg);
	
	temreg = read_reg(EXTI_RTSR, ~(0x01u << 2));
	temreg = temreg | (0x01u << 2);
	write_reg(EXTI_RTSR, temreg);
	
	/*SYSCFG*/
	temreg = read_reg(SYSCFG_EXTICR1, ~(0xF << 0));
	temreg = temreg | (0x00 << 0);
	write_reg(SYSCFG_EXTICR1, temreg);
	
	/*NVIC*/
	//User button
	temreg = read_reg(NVIC_PRI1, ~(0xFF << 8));
	temreg = temreg | (0x01 << 14);
	write_reg(NVIC_PRI1, temreg);
	
	temreg = read_reg(NVIC_ISER, ~(0x1 << 5));
	temreg = temreg | (0x01 << 5);
	write_reg(NVIC_ISER, temreg);
	
	//PA2 interrupt
	temreg = read_reg(NVIC_PRI1, ~(0xFF << 16));
	temreg = temreg | (0x02 << 22);
	write_reg(NVIC_PRI1, temreg);
	
	temreg = read_reg(NVIC_ISER, ~(0x1 << 6));
	temreg = temreg | (0x01 << 6);
	write_reg(NVIC_ISER, temreg);
	
	/*enable global interrupt*/
	asm("cpsie i");
}



void main(void)
{
	enable_clk();
	init_pin();
	init_interrupt();
	while(1)
	{
		led_on(LD4_PIN);
		delay(0xFF);
		led_off(LD4_PIN);
		delay(0xFF);
	}
}




