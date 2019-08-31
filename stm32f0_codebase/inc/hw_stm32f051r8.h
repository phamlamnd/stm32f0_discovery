#ifndef _HW_STM32F051R8_H_
#define _HW_STM32F051R8_H_

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

typedef struct
{
	volatile unsigned int CR1;		//Control register 1
	volatile unsigned int CR2;		//Control register 2
	volatile unsigned int CR3;		//Control register 3
	volatile unsigned int BRR;		//Baud rate register
	volatile unsigned int GTPR;		//Guard time and prescaler register
	volatile unsigned int RTOR;		//Receiver timeout register
	volatile unsigned int RQR;		//Request register
	volatile unsigned int ISR;		//Interrupt and status register
	volatile unsigned int ICR;		//Interrupt flag clear register
	volatile unsigned int RDR;		//Receive data register
	volatile unsigned int TDR;		//Transmit data register
	
}USART_TypeDef;


/*=======================I/O PIN======================*/
#define LD3_PIN 9		//PC9
#define LD4_PIN 8		//PC8
#define USER_BUTTON 0	//PA0

/*=======================FLASH/RAM BASE==============*/
#define FLASH_BASE			(unsinged int)0x08000000U	
#define SRAM_BASE			(unsigned int)0x20000000U
#define PERIPH_BASE			(unsigned int)0x40000000U
#define APBPERIPH_BASE		(PERIPH_BASE)
#define AHB1PERIPH_BASE		(PERIPH_BASE + 0x0020000U)
#define AHB2PERIPH_BASE		(PERIPH_BASE + 0x8000000U)

/*=======================GPIO=======================*/
#define GPIOA_BASE			(unsigned int)0x48000000U
#define GPIOB_BASE			(unsigned int)0x48000400U
#define GPIOC_BASE			(unsigned int)0x48000800U
#define GPIOD_BASE			(unsigned int)0x48000C00U
#define GPIOE_BASE			(unsigned int)0x48001000U
#define GPIOF_BASE			(unsigned int)0x48001400U
#define GPIOA				((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC				((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE				((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF				((GPIO_TypeDef*)GPIOF_BASE)

/*GPIO port mode register (GPIOx_MODER)*/
#define GPIO_MODE_INPUT			0x00000000U
#define GPIO_MODE_OUTPUT		0x00000001U
#define GPIO_MODE_AF			0x00000002U
#define GPIO_MODE_ANALOG		0x00000003U
/*GPIO port output type register (GPIOx_OTYPER)*/
#define OUTPUT_PP				0x00000000U
#define OUTPUT_OD				0x00000001U
/*GPIO port output speed register (GPIOx_OSPEEDR)*/
#define OUTPUT_LOWSPEED			0x00000000U
#define OUTPUT_MEDIUMSPEED		0x00000001U
#define OUTPUT_HIGHSPEED		0x00000003U
/*GPIO port pull-up/pull-down register (GPIOx_PUPDR)*/
#define GPIO_NOPULL        		0x00000000U
#define GPIO_PULLUP        		0x00000001U 
#define GPIO_PULLDOWN      		0x00000002U


/*=======================RCC========================*/
#define RCC_BASE			(unsigned int)0x40021000U
#define RCC					((RCC_TypeDef*)RCC_BASE)

/*CFGR: Bits 10:8 PPRE[2:0]: PCLK prescaler*/
#define HCLK_NODIV				0x0
#define HCLK_DIV2				0x4
#define HCLK_DIV4				0x5
#define HCLK_DIV8				0x6
#define HCLK_DIV16				0x7

/*CFGR: Bits 7:4 HPRE[3:0]: HCLK prescaler*/
#define SYSCLK_NODIV			0x0
#define SYSCLK_DIV2				0x8
#define SYSCLK_DIV4				0x9
#define SYSCLK_DIV8				0xA
#define SYSCLK_DIV16			0xB
#define SYSCLK_DIV64			0xC
#define SYSCLK_DIV128			0xD
#define SYSCLK_DIV256			0xE
#define SYSCLK_DIV512			0xF

/*CFGR: Bits 1:0 SW[1:0]: System clock switch*/
#define SYSCLK_SOURCE_HSI		0x0
#define SYSCLK_SOURCE_HSE		0x1
#define SYSCLK_SOURCE_PLL		0x2
#define SYSCLK_SOURCE_HSI48		0x3

/*CFGR3: Bits 1:0 USART1SW[1:0]: USART1 clock source selection*/
#define USART1_SOURCE_PCLK		0x0
#define USART1_SOURCE_SYSCLK	0x1
#define USART1_SOURCE_LSE		0x2
#define USART1_SOURCE_HSI		0x3

/*=======================NVIC=======================*/
#define NVIC_BASE			(unsigned int)0xE000E100U
#define NVIC				((NVIC_TypeDef*)NVIC_BASE)

/*=======================SYSCFG=====================*/
#define SYSCFG_BASE			(unsigned int)0x40010000U
#define SYSCFG				((SYSCFG_TypeDef*)SYSCFG_BASE)

/*=======================EXTI=======================*/
#define EXTI_BASE			(unsigned int)0x40010400U
#define EXTI				((EXTI_TypeDef*)EXTI_BASE)

/*=======================SYSTICK====================*/
#define STK_BASE			(unsigned int)0xE000E010U
#define STK					((STK_TypeDef*)STK_BASE)

/*========================USART=====================*/
#define USART1_BASE			(unsigned int)0x40013800U
#define USART2_BASE			(unsigned int)0x40004400U
#define USART1				((USART_TypeDef*)USART1_BASE)
#define USART2				((USART_TypeDef*)USART2_BASE)

#endif /*_HW_STM32F051R8_H_*/
