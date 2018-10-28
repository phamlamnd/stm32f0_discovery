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

void Delay_us(unsigned char us)
{
	unsigned char i;
	for(i = 0; i < us; i++)
	{
		asm("nop");
	}
}

void Init_TM1637()	//CLK:PB8, DIO:PB9
{
	RCC->AHBENR |= 0x01<<18;	//Enable clock GPIOB
	GPIOB->MODER &= ~(0x03<<16);
	GPIOB->MODER |= 0x01<<16;
	GPIOB->OTYPER &= ~(0x01<<8);
	
	GPIOB->MODER &= ~(0x03<<18);
	GPIOB->MODER |= 0x01<<18;
	GPIOB->OTYPER &= ~(0x01<<9);
	
	GPIOB->ODR &= ~(0x01<<8); //CLK LOW LEVEL
	GPIOB->ODR &= ~(0x01<<9); //DIO LOW LEVEL
	
}

void start() //CLK:PB8 HIGH LEVEL, DIO:PB9 FROM HIGH TO LOW
{
	GPIOB->ODR |= 0x01<<9; //DIO FROM HIGH LEVEL
	GPIOB->ODR |= 0x01<<8; //CLK HIGH LEVEL
	GPIOB->ODR &= ~(0x01<<9); //DIO LOW LEVEL
	GPIOB->ODR &= ~(0x01<<8); //CLK LOW LEVEL
}

void stop() //CLK:PB8 HIGH LEVEL, DIO:PB9 FROM LOW TO HIGH
{
	GPIOB->ODR &= ~(0x01<<9); //DIO FROM LOW LEVEL
	GPIOB->ODR |= 0x01<<8; //CLK HIGH LEVEL
	GPIOB->ODR |= 0x01<<9; //DIO TO HIGH LEVEL
	GPIOB->ODR &= ~(0x01<<8); //CLK LOW LEVEL
}

void Ack()
{
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
	GPIOB->MODER &= ~(0x03<<18);
	GPIOB->PUPDR &= ~(0x03<<18);
	GPIOB->PUPDR |= 0x01<<18;
	while(GPIOB->IDR & 0x01<<9) //read data  PB9
	GPIOB->MODER &= ~(0x03<<18);
	GPIOB->MODER |= 0x01<<18;
	GPIOB->OTYPER &= ~(0x01<<9);
	GPIOB->ODR |= 0x01<<8; //CLK = 1
	GPIOB->ODR &= ~(0x01<<8); //CLK = 0
}

void WriteByte(unsigned char oneByte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		if(oneByte & 0x01)
		{
			GPIOB->ODR |= 0x01<<9;
		}
		else
		{
			GPIOB->ODR &= ~(0x01<<9);
		}
		GPIOB->ODR |= 0x01<<8; //CLK = 1
		GPIOB->ODR &= ~(0x01<<8); //CLK = 0
		oneByte >>= 1;
	}
}
const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

void Display(unsigned char ngan, unsigned char tram, unsigned char chuc, unsigned char donvi)
{
	start();
	WriteByte(0x40);
	Ack();
	stop();
	
	start();
	WriteByte(0xC0);
	Ack();
	WriteByte(segmentMap[ngan]);
	Ack();
	WriteByte(segmentMap[tram] | 0x80);
	Ack();
	WriteByte(segmentMap[chuc]);
	Ack();
	WriteByte(segmentMap[donvi]);
	Ack();
	stop();
	
	start();
	WriteByte(0x88);
	Ack();
	stop();
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

volatile unsigned char ngan = 0, tram = 0, chuc = 0, donvi = 0;
unsigned int temp = 0;
void SysTick_Handler(void)
{
	if(temp == 0)
	{
		Led_On(LD4_PIN);
		temp = 1;	
		Display(ngan, tram, chuc, donvi);
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
	STK->RVR = 0x3D0900;	//7A1200(1s), 3D0900(0.5s), FD2400(0.25s), 186A00(0.2s), C3500(0.1s)
}



void main(void)
{
	ngan = tram = chuc = donvi = 0;
	Enable_Clk();
	Init_Pin();
	Init_SysTick();
	Init_TM1637();
	while(1)
	{
		
	}
}