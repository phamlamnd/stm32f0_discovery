#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__

typedef struct
{
	volatile unsigned int MODER;	//GPIO port mode register
	volatile unsigned int OTYPER;	//GPIO port output type register
	volatile unsigned int OSPEEDR;	//GPIO port output speed register
	volatile unsigned int PUPDR;	//GPIO port pull-up/pull-down register	
	volatile unsigned int IDR;		//GPIO port input data register
	volatile unsigned int ODR;		//GPIO port output data register 
	volatile unsigned int BSRR;		//GPIO port bit set/reset register
	volatile unsigned int LCKR;		//GPIO port configuration lock register
	volatile unsigned int AFRL;		//GPIO alternate function low register
	volatile unsigned int AFRH;		//GPIO alternate function high register
	volatile unsigned int BRR;		//GPIO port bit reset register
}GPIO_TypeDef;

typedef struct
{
	volatile unsigned int CR;		//Clock control register
	volatile unsigned int CFGR;		//Clock configuration register
	volatile unsigned int CIR;		//Clock interrupt register
	volatile unsigned int APB2RSTR; //APB2 peripheral reset register
	volatile unsigned int APB1RSTR; //APB1 peripheral reset register
	volatile unsigned int AHBENR;	//AHB Peripheral Clock enable registe
	volatile unsigned int APB2ENR;	//APB2 peripheral clock enable register
	volatile unsigned int APB1ENR;	//APB1 peripheral clock enable register
	volatile unsigned int BDCR;		//Backup domain control register
	volatile unsigned int CSR;		//Control/status register
	volatile unsigned int AHBRSTR;	//AHB peripheral clock reset register 
	volatile unsigned int CFGR2;	//Clock configuration register2
	volatile unsigned int CFGR3;	//Clock configuration register3
	volatile unsigned int CR2;		//Clock control register 2
}RCC_TypeDef;

typedef struct
{
	volatile unsigned int ISER;			//Interrupt Set-enable Register, 	address: 0xE000E100
			 unsigned int RESERVED0[31];//
	volatile unsigned int ICER;			//Interrupt Clear-enable Register, 	address: 0xE000E180
			 unsigned int RESERVED1[31];//
	volatile unsigned int ISPR;			//Interrupt Set-pending Register, 	address: 0xE000E200
			 unsigned int RESERVED2[31];//
	volatile unsigned int ICPR;			//Interrupt Clear-pending Register, address: 0xE000E280
			 unsigned int RESERVED3[95];//
	volatile unsigned int IPR[8];		//Interrupt Priority Registers, address: 0xE000E400-0xE000E41C
}NVIC_TypeDef;

typedef struct
{
	volatile unsigned int CFGR1;		//SYSCFG configuration register 1
			 unsigned int RESERVED0[1];	//
	volatile unsigned int EXTICR[4];	//SYSCFG external interrupt configuration register 1-4		
	volatile unsigned int CFGR2;		//SYSCFG configuration register 2
}SYSCFG_TypeDef;

typedef struct
{
	volatile unsigned int IMR;		//Interrupt mask register
	volatile unsigned int EMR;		//Event mask register 
	volatile unsigned int RTSR;		//Rising trigger selection register
	volatile unsigned int FTSR;		//Falling trigger selection register
	volatile unsigned int SWIER;	//Software interrupt event register 
	volatile unsigned int PR;		//Pending register
}EXTI_TypeDef;

typedef struct
{
	volatile unsigned int CSR;		//RW, SysTick Control and Status Register 
	volatile unsigned int RVR;		//RW, SysTick Reload Value Register
	volatile unsigned int CVR;		//RW, SysTick Current Value Register 
	volatile unsigned int CALIB;	//RO, SysTick Calibration Value Register
}STK_TypeDef;

/*Define I/O PIN*/
#define LD3_PIN 9		//PC9
#define LD4_PIN 8		//PC8
#define USER_BUTTON 0	//PA0

#define FLASH_BASE			(unsinged int)0x08000000U		//FLASH address base
#define SRAM_BASE			(unsigned int)0x20000000U		//SRAM address base
#define PERIPH_BASE			(unsigned int)0x40000000U		//PERIPHERAL address base
#define NVIC_BASE			(unsigned int)0xE000E100U		//NVIC address base
#define STK_BASE			(unsigned int)0xE000E010U		//SysTick address base

#define APBPERIPH_BASE		(PERIPH_BASE)
#define AHB1PERIPH_BASE		(PERIPH_BASE + 0x0020000U)
#define AHB2PERIPH_BASE		(PERIPH_BASE + 0x8000000U)

#define GPIOA_BASE			(unsigned int)0x48000000U
#define GPIOB_BASE			(unsigned int)0x48000400U
#define GPIOC_BASE			(unsigned int)0x48000800U
#define GPIOD_BASE			(unsigned int)0x48000C00U
#define GPIOE_BASE			(unsigned int)0x48001000U
#define GPIOF_BASE			(unsigned int)0x48001400U
#define RCC_BASE			(unsigned int)0x40021000U
#define SYSCFG_BASE			(unsigned int)0x40010000U
#define EXTI_BASE			(unsigned int)0x40010400U

#define GPIOA				((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC				((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE				((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF				((GPIO_TypeDef*)GPIOF_BASE)
#define RCC					((RCC_TypeDef*)RCC_BASE)
#define NVIC				((NVIC_TypeDef*)NVIC_BASE)
#define SYSCFG				((SYSCFG_TypeDef*)SYSCFG_BASE)
#define EXTI				((EXTI_TypeDef*)EXTI_BASE)
#define STK					((STK_TypeDef*)STK_BASE)

#endif
