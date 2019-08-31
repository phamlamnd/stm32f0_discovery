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
	systick_init();
	while(1)
	{
		/* do nothing */
	}
}