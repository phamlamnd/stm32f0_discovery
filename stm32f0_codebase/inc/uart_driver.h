#ifndef UART_DRIVER_H
#define UART_DRIVER_H
#include "hw_stm32f051r8.h"

void UART_DRV_Init(void);
char UART_DRV_SendByte(unsigned char data_input);
void UART_DRV_SendString(unsigned char *str_data);

#endif /* UART_DRIVER_H */