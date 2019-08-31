#ifndef TM1637_DRIVER_H
#define TM1637_DRIVER_H

#include "hw_stm32f051r8.h"

void TM1637_DRV_Init(void);
void TM1637_DRV_Display(unsigned char digit4, unsigned char digit3,
                        unsigned char digit2, unsigned char digit1);

#endif /* TM1637_DRIVER_H */