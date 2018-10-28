
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
	write_reg(RCC_AHBENR, temreg);
}

void init_pin(void)
{
	unsigned int temreg;
	temreg = read_reg(GPIOC_MODER, ~(0x03 << 18));
	temreg = temreg | GPIOC_MODER_OUTPUT << 18;
	write_reg(GPIOC_MODER, temreg);
	
	temreg = read_reg(GPIOA_MODER, ~(0x03 << 0));
	temreg = temreg | GPIOA_MODER_INPUT << 0;
	write_reg(GPIOA_MODER, temreg);
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
	unsigned int state_idr_reg;
	unsigned int led_state = 0;
	enable_clk();
	init_pin();
	while(1)
	{
		/*polling*/
		state_idr_reg = read_reg(GPIOA_IDR, (0x1u << USER_BUTTON));
		if(state_idr_reg == 0x01u)
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
	}
}




