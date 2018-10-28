#ifndef __USART_H__
#define __USART_H__
#include "hw_stm32f051r8.h"


void usart_init(void);
char usart_send_byte(unsigned char data_input);
void usart_send_string(unsigned char *str_data);

#endif /*__USART_H__*/