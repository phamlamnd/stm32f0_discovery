#include "tm1637.h"

void delay_us(unsigned char us)
{
	unsigned char i;
	for(i = 0; i < us; i++)
	{
		asm("nop");
	}
}

void tm1637_init()
{
	/*Enable clock GPIOB*/
	RCC->AHBENR |= GPIOB_CLOCK_EN;
	
	/*Init TM1637_CLK PIN*/
	GPIOB->MODER &= ~GPIO_MODER_MASK(TM1637_CLK);
	GPIOB->MODER |= GPIO_MODER_OUTPUT(TM1637_CLK);
	GPIOB->OTYPER &= ~GPIO_OTYPER_MASK(TM1637_CLK);
	
	/*Init TM1637_DIO PIN*/
	GPIOB->MODER &= ~GPIO_MODER_MASK(TM1637_DIO);
	GPIOB->MODER |= GPIO_MODER_OUTPUT(TM1637_DIO);
	GPIOB->OTYPER &= ~GPIO_OTYPER_MASK(TM1637_DIO);
	
	GPIOB->ODR &= ~(1U<<TM1637_CLK); 	//CLK LOW LEVEL
	GPIOB->ODR &= ~(1U<<TM1637_DIO); 	//DIO LOW LEVEL
	
}

void start() //CLK:PB8 HIGH LEVEL, DIO:PB9 FROM HIGH TO LOW
{
	GPIOB->ODR |= 1U<<TM1637_DIO; 		//DIO FROM HIGH LEVEL
	GPIOB->ODR |= 1U<<TM1637_CLK; 		//CLK HIGH LEVEL
	GPIOB->ODR &= ~(1U<<TM1637_DIO); 	//DIO LOW LEVEL
	GPIOB->ODR &= ~(1U<<TM1637_CLK); 	//CLK LOW LEVEL
}

void stop() //CLK:PB8 HIGH LEVEL, DIO:PB9 FROM LOW TO HIGH
{
	GPIOB->ODR &= ~(1U<<TM1637_DIO); 	//DIO FROM LOW LEVEL
	GPIOB->ODR |= 1U<<TM1637_CLK; 		//CLK HIGH LEVEL
	GPIOB->ODR |= 1U<<TM1637_DIO; 		//DIO TO HIGH LEVEL
	GPIOB->ODR &= ~(1U<<TM1637_CLK); 	//CLK LOW LEVEL
}

void ack()
{
	GPIOB->ODR &= ~(1U<<TM1637_CLK); 				//CLK LOW LEVEL
	GPIOB->MODER &= ~GPIO_MODER_MASK(TM1637_DIO);	//DIO input mode	
	GPIOB->MODER |= GPIO_MODER_INPUT(TM1637_DIO);
	GPIOB->PUPDR &= ~GPIO_PUPDR_MASK(TM1637_DIO);
	GPIOB->PUPDR |= GPIO_PUPDR_PULL_UP(TM1637_DIO);
	while(GPIOB->IDR & (1U<<TM1637_DIO)); 			//read data DIO
	GPIOB->MODER &= ~GPIO_MODER_MASK(TM1637_DIO);	//DIO output mode
	GPIOB->MODER |= GPIO_MODER_OUTPUT(TM1637_DIO);
	GPIOB->OTYPER &= ~GPIO_OTYPER_MASK(TM1637_DIO);
	GPIOB->ODR |= 1U<<TM1637_CLK; 					//CLK HIGH LEVEL
	GPIOB->ODR &= ~(1U<<TM1637_CLK); 				//CLK LOW LEVEL
}

void write_byte(unsigned char one_byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		if(one_byte & 1U)
		{
			GPIOB->ODR |= 1U<<TM1637_DIO;
		}
		else
		{
			GPIOB->ODR &= ~(1U<<TM1637_DIO);
		}
		GPIOB->ODR |= 1U<<TM1637_CLK; 				//CLK HIGH LEVEL
		GPIOB->ODR &= ~(1U<<TM1637_CLK); 			//CLK LOW LEVEL
		one_byte >>= 1;
	}
}

const char segmentMap[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0-9
void tm1637_display(unsigned char digit4, unsigned char digit3,
					unsigned char digit2, unsigned char digit1)
{
	start();
	write_byte(0x40);
	ack();
	stop();
	
	start();
	write_byte(0xC0);
	ack();
	write_byte(segmentMap[digit4]);
	ack();
	write_byte(segmentMap[digit3] | 0x80);
	ack();
	write_byte(segmentMap[digit2]);
	ack();
	write_byte(segmentMap[digit1]);
	ack();
	stop();
	
	start();
	write_byte(0x89);
	ack();
	stop();
}