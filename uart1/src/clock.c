#include "clock.h"

void system_init(void)
{ 
	/*Set HSION bit*/
	RCC->CR |= (unsigned int)0x00000001U;
	/*Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits*/
	RCC->CFGR &= (unsigned int)0xF8FFB80CU;  
	/*Reset HSEON, CSSON and PLLON bits*/
	RCC->CR &= (unsigned int)0xFEF6FFFFU;
	/*Reset HSEBYP bit*/
	RCC->CR &= (unsigned int)0xFFFBFFFFU;
	/*Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits*/
	RCC->CFGR &= (unsigned int)0xFFC0FFFFU;
	/*Reset PREDIV[3:0] bits*/
	RCC->CFGR2 &= (unsigned int)0xFFFFFFF0U;
	/*Reset USART1SW[1:0], I2C1SW, CECSW and ADCSW bits*/
	RCC->CFGR3 &= (unsigned int)0xFFFFFEACU;
	/*Reset HSI14 bit*/
	RCC->CR2 &= (unsigned int)0xFFFFFFFEU;
	/*Disable all interrupts*/
	RCC->CIR = 0x00000000U;
}

void system_clock_config()
{
	/*HSI clock enable*/
	RCC->CR |= HSI_OSCILLATOR_ON;
	
#if 0
	/*select SYSCLK source HSI*/
	RCC->CFGR |= SYSCLK_SOURCE_HSI;
	/*division factor of the AHB clock*/
	RCC->CFGR |= SYSCLK_NODIV;
	/*division factor of the APB clock*/
	RCC->CFGR |= HCLK_NODIV;
	/*selected USART1 clock source*/
	RCC->CFGR3 |= USART1_SOURCE_PCLK;
#endif

#if 1
	/*PLL DISABLE*/
	RCC->CR &= PLL_DISABLE;
	
	/*PLL SOURCE HSI*/
	RCC->CFGR &= ~(1U<<16);
	
	/*PLLMUL*/
	RCC->CFGR &= ~(PLLMUL_MASK);
	RCC->CFGR |= PLLMUL4;
	
	/*SYSCLK SOURCE: PLL*/
	RCC->CFGR |= SYSCLK_SOURCE_PLL;
	
	/*SYSCLK DIV*/
	RCC->CFGR &= ~(15U<<4);
	RCC->CFGR |= SYSCLK_DIV2;
	
	/*HCLK DIV*/
	RCC->CFGR &= ~(7U<<8);
	RCC->CFGR |= HCLK_NODIV;
	
	/*PLL ON*/
	RCC->CR |= PLL_ENABLE;
	
	/*USART1 Clock source*/
	RCC->CFGR3 |= USART1_SOURCE_HSI;
#endif
}

void clock_enable(void)
{	
	/*Enable clock GPIOA*/
	RCC->AHBENR |= GPIOA_CLOCK_EN;
	/*Enable clock GPIOB*/
	RCC->AHBENR |= GPIOB_CLOCK_EN;
	/*Enable clock GPIOC*/
	RCC->AHBENR |= GPIOC_CLOCK_EN;
	/*Enable clock UART1*/
	RCC->APB2ENR |= USART1_CLOCK_EN;
	/*Enable clock SYSCFG*/
	RCC->APB2ENR |= SYSCFG_CLOCK_EN;
}

void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm("nop");
        }
    }
}