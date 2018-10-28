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

volatile unsigned int temp = 0;
void SysTick_Handler(void)
{
	if(temp == 0)
	{
		Led_On(LD4_PIN);
		temp = 1;
	}
	else
	{
		Led_Off(LD4_PIN);
		temp = 0;
	}
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

void EXTI4_15_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}	

/**********************************************************/

void Enable_Clk(void)
{
	//HSI ON by default
	RCC->CR |= 0x01<<0;
	
	//Enable clock GPIOA
	RCC->AHBENR |= 0x01<<17;
	
	//Enable clock GPIOC
	RCC->AHBENR |= 0x01<<19;
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
}

void Init_SysTick()
{
	//SYSCLK not divided
	RCC->CFGR &= ~(0x0F<<4);
	//SysTick counter enable, interrupt enable, clksourse: processor
	STK->CSR |= 0x07<<0;
	//Reaload value
	STK->RVR = 0x3D0900;
}

void Init_TM1637()
{
	//Enable clock for GPIOB
	RCC->AHBENR |= 0x01<<18;
	//Set PB8 as CLK, PB9 as DIO output
	GPIOB->MODER &= ~(0x03<<16);
	GPIOB->MODER |= 0x01<<16;
	GPIOB->OTYPER &= ~(0x01<<8);
	
	GPIOB->MODER &= ~(0x03<<18);
	GPIOB->MODER |= 0x01<<18;
	GPIOB->OTYPER &= ~(0x01<<9);
	
	GPIOB->ODR &= ~(0x01<<8);	
	GPIOB->ODR &= ~(0x01<<9);

}

void start()
{
	GPIOB->ODR |= 0x01<<8; //CLK = 1
	GPIOB->ODR |= 0x01<<9; //DIO = 1
	GPIOB->ODR &= ~(0x01<<9); //DIO = 0
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
}

void stop()
{
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
	GPIOB->ODR &= ~(0x01<<9); //DIO = 0
	GPIOB->ODR |= 0x01<<8; //CLK = 1
	GPIOB->ODR |= 0x01<<9; //DIO = 1
}

void Delay_us(unsigned int i) // n us delay
{
	for (;i > 0; i--)
	{
		asm("nop");
	}
}

void I2CStart(void) // 1637 start
{
	GPIOB->ODR |= 0x01<<8; //CLK = 1
	GPIOB->ODR |= 0x01<<9; //DIO = 1
	Delay_us(2);
	GPIOB->ODR &= ~(0x01<<9); //DIO = 0
}

void I2Cask(void) // 1637 Answer
{
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
	Delay_us(5); // After the falling edge of the eighth clock delay 5us, ACK signals the beginning of judgment
	GPIOB->MODER &= ~(0x03<<18);
	GPIOB->PUPDR &= ~(0x03<<18);
	GPIOB->PUPDR |= 0x01<<18;
	while (GPIOB->IDR&(0x01<<9)); //DIO
	GPIOB->MODER &= ~(0x03<<18);
	GPIOB->MODER |= 0x01<<18;
	GPIOB->OTYPER &= ~(0x01<<9);
	GPIOB->ODR |= 0x01<<8; //CLK = 1
	Delay_us(2);
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
}

void I2CStop(void) // 1637 Stop
{
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
	Delay_us(2);
	GPIOB->ODR &= ~(0x01<<9); //DIO = 0
	Delay_us(2);
	GPIOB->ODR |= 0x01<<8; //CLK = 1
	Delay_us(2);
	GPIOB->ODR |= 0x01<<9; //DIO = 1
}

void I2CWrByte(unsigned char oneByte) // write a byte
{
	unsigned char i;
	for (i = 0; i <8; i++)
	{
		GPIOB->ODR &= ~(0x01<<8); //CLK = 0
		if (oneByte & 0x01) // low front
		{
			GPIOB->ODR |= 0x01<<9; //DIO = 1
		}
		else
		{
			GPIOB->ODR &= ~(0x01<<9); //DIO = 0
		}
		Delay_us(3);
		oneByte = oneByte>>1;
		GPIOB->ODR |= 0x01<<8; //CLK = 1
		Delay_us(3);
   }
}

const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

unsigned int dot = 1;
void SmgDisplay(unsigned int ngan, unsigned int tram, unsigned int chuc, unsigned int donvi) // Write display register
{
	unsigned int num = 5673;
	I2CStart();
	I2CWrByte(0x40); //40H address is automatically incremented by 1 mode, 44H fixed address mode
	I2Cask();
	I2CStop();
	
	I2CStart();
	I2CWrByte(0xc0); // Set the first address
	I2Cask();
	
	I2CWrByte(segmentMap[ngan]); // Send data
	I2Cask();
	if(dot == 0)
	{
		I2CWrByte(segmentMap[tram] | 0x80); 
		dot = 1;
	}
	else	
	{
		I2CWrByte(segmentMap[tram]); 
		dot = 0;
	}

	I2Cask();
	I2CWrByte(segmentMap[chuc]); 
	I2Cask();
	I2CWrByte(segmentMap[donvi]); 
    I2Cask();
    I2CStop();
	
    I2CStart();
	I2CWrByte(0x89); // Open display, maximum brightness
	I2Cask();
	I2CStop();
}

void main(void)
{
	unsigned int donvi = 0;
	unsigned int chuc = 0;
	unsigned int tram = 0;
	unsigned int ngan = 0;
	Enable_Clk();
	Init_Pin();
	//Init_SysTick();
	Init_TM1637();
	
	while(1)
	{
		SmgDisplay(ngan, tram, chuc, donvi);
		Led_Off(LD3_PIN);
		Delay(0x30);
		Delay(0x30);
		
		donvi++;
		if(donvi == 10)
		{
			donvi = 0;
			chuc = chuc+1;
		}
		if(chuc == 6)
		{
			chuc = 0;
			tram = tram+1;
		}
		if(tram == 10)
		{
			tram = 0;
			ngan = ngan+1;
		}
		if(ngan == 6)
		{
			ngan = 0;
		}
		
		Led_On(LD3_PIN);
		SmgDisplay(ngan, tram, chuc, donvi);
		Delay(0x30);
		Delay(0x30);
	}
}