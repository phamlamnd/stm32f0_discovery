#include "tm1637.h"

void delay_us(unsigned char us)
{
	unsigned char i;
	for(i = 0; i < us; i++)
	{
		asm("nop");
	}
}

void tm1637_init(void)	//CLK:PB8, DIO:PB9
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

void start(void) //CLK:PB8 HIGH LEVEL, DIO:PB9 FROM HIGH TO LOW
{
	GPIOB->ODR |= 0x01<<9; //DIO FROM HIGH LEVEL
	GPIOB->ODR |= 0x01<<8; //CLK HIGH LEVEL
	GPIOB->ODR &= ~(0x01<<9); //DIO LOW LEVEL
	GPIOB->ODR &= ~(0x01<<8); //CLK LOW LEVEL
}

void stop(void) //CLK:PB8 HIGH LEVEL, DIO:PB9 FROM LOW TO HIGH
{
	GPIOB->ODR &= ~(0x01<<9); //DIO FROM LOW LEVEL
	GPIOB->ODR |= 0x01<<8; //CLK HIGH LEVEL
	GPIOB->ODR |= 0x01<<9; //DIO TO HIGH LEVEL
	GPIOB->ODR &= ~(0x01<<8); //CLK LOW LEVEL
}

void ack(void)
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

void write_byte(unsigned char one_byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		if(one_byte & 0x01)
		{
			GPIOB->ODR |= 0x01<<9;
		}
		else
		{
			GPIOB->ODR &= ~(0x01<<9);
		}
		GPIOB->ODR |= 0x01<<8; //CLK = 1
		GPIOB->ODR &= ~(0x01<<8); //CLK = 0
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
	write_byte(0x88);
	ack();
	stop();
}