#include "clock.h"
#include "gpio.h"
#include "tm1637.h"
#include "interrupt.h"
#include "systick.h"
#include "usart.h"

void main(void)
{
	system_init();
	system_clock_config();
	clock_enable();
	gpio_init();
	usart_init();
	systick_init();
	systick_interrupt_enable(0x3D08FFU);
	
	unsigned char x = 'A';
	while(1)
	{
		usart_send_byte(x);
		delay(0x20);
		x++;
		if(x == 'Z')
		{
			x = 'A';
		}
	}
}