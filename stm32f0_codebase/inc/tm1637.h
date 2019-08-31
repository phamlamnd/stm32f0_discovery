#ifndef __TM1637_H__
#define __TM1637_H__

#include "hw_stm32f051r8.h"

void delay_us(unsigned char us);
void tm1637_init(void);
void start(void);
void stop(void);
void ack(void );
void write_byte(unsigned char one_byte);
void tm1637_display(unsigned char digit4, unsigned char digit3, unsigned char digit2, unsigned char digit1);

#endif /*__TM1637_H__*/