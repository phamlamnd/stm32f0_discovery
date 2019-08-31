#include "clock_driver.h"

void CLOCK_DRV_Init(void)
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

void CLOCK_DRV_Config()
{
    /*HSI clock enable*/
    RCC->CR |= 0x01;
    /*select SYSCLK source HSI*/
    RCC->CFGR |= SYSCLK_SOURCE_HSI;
    /*division factor of the AHB clock*/
    RCC->CFGR |= SYSCLK_NODIV<<4;
    /*division factor of the APB clock*/
    RCC->CFGR |= HCLK_NODIV<<8;
    /*selected USART1 clock source*/
    RCC->CFGR3 |= USART1_SOURCE_PCLK;
}

void CLOCK_DRV_Enable(void)
{
    /*Enable clock GPIOA*/
    RCC->AHBENR |= 0x01<<17;
    /*Enable clock GPIOC*/
    RCC->AHBENR |= 0x01<<19;
    /*Enable clock UART1*/
    RCC->APB2ENR |= 0x01<<14;
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
