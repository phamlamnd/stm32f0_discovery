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
	char ch = 'A';
	while(1)
	{
		usart_send_byte(ch);
		delay(0x50);
		ch++;
		if(ch > 'Z')
		ch = 'A';
	
	}
}