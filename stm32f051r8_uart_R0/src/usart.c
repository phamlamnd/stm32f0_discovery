#include "usart.h"

void usart_init(void)
{
	/*Disable USART module*/
	USART1->CR1 &= ~(0x01<<0);
	/*1 start bit, 8 data bits, n stop bits*/
	USART1->CR1 &= ~(0x01<<12);	/*M0 = 0*/
	USART1->CR1 &= ~(0x01<<28); /*M1 = 0*/
	/*Parity disable [PCE] = 0*/
	USART1->CR1 &= ~(0x01<<10);
	/*1 stop bit STOP = 00*/
	USART1->CR2 &= ~(0x03<<12);
	/*Oversampling by 16:Tx/Rx baud = fck/USARTDIV*/
	USART1->CR1 &= ~(0x01<<15);	/*OVER8 = 0, Oversampling by 16*/
	/*Select baud rate: oversampling by 16 -> fck = 8Mhz, baud = 9600
	USART1DIV = 8000000/9600 = 833d = 341h*/
	USART1->BRR &= 0x00;	/*reset register*/
	USART1->BRR |= 0x341;
	/*Enable USART module UE = 1*/
	USART1->CR1 |= 0x01<<0;
	/*Transmitter enable TE = 1*/
	USART1->CR1 |= 0x01<<3;
}

char usart_send_byte(unsigned char data_input)
{
	/*check TXE: Transmit data register empty*/
	char state = 0;
	if(USART1->ISR & (0x01<<7))
	{
		USART1->TDR = (unsigned int)data_input;
	}
	else
	{
		state = -1;
	}
	return state;
}

void usart_send_string(unsigned char *str_data)
{
	while(*str_data)
	{
		if(0 == usart_send_byte(*str_data))
		{
			str_data++;
		}	
	}
}