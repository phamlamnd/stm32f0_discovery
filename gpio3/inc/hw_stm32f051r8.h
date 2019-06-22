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
	volatile unsigned int ISER;				//Interrupt Set-enable Register, 	address: 0xE000E100
			 unsigned int RESERVED0[31];	//RESERVED
	volatile unsigned int ICER;				//Interrupt Clear-enable Register, 	address: 0xE000E180
			 unsigned int RESERVED1[31];	//RESERVED
	volatile unsigned int ISPR;				//Interrupt Set-pending Register, 	address: 0xE000E200
			 unsigned int RESERVED2[31];	//RESERVED
	volatile unsigned int ICPR;				//Interrupt Clear-pending Register, address: 0xE000E280
			 unsigned int RESERVED3[95];	//RESERVED
	volatile unsigned int IPR[8];			//Interrupt Priority Registers, address: 0xE000E400-0xE000E41C
}NVIC_TypeDef;


typedef struct
{
	volatile unsigned int CFGR1;		//SYSCFG configuration register 1
			 unsigned int RESERVED0[1];	//RESERVED
	volatile unsigned int EXTICR1;		//SYSCFG external interrupt configuration register 1
	volatile unsigned int EXTICR2;		//SYSCFG external interrupt configuration register 2
	volatile unsigned int EXTICR3;		//SYSCFG external interrupt configuration register 3	
	volatile unsigned int EXTICR4;		//SYSCFG external interrupt configuration register 4
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


/*=======================PIN DEFINE===============*/
#define LD3_PIN 		9		//PC9
#define LD4_PIN 		8		//PC8
#define USER_BUTTON 	0		//PA0
#define USART1_TX		9		//PA9
#define USART1_RX		10		//PA10
#define TM1637_CLK		8		//PB8
#define TM1637_DIO		9		//PB9			


/*=======================FLASH/RAM BASE==============*/
#define FLASH_BASE			((unsinged int)0x08000000U)	
#define SRAM_BASE			((unsigned int)0x20000000U)
#define PERIPH_BASE			((unsigned int)0x40000000U)
#define APBPERIPH_BASE		(PERIPH_BASE)
#define AHB1PERIPH_BASE		(PERIPH_BASE + 0x0020000U)
#define AHB2PERIPH_BASE		(PERIPH_BASE + 0x8000000U)

/*=======================GPIO=======================*/
#define GPIOA_BASE			((unsigned int)0x48000000U)
#define GPIOB_BASE			((unsigned int)0x48000400U)
#define GPIOC_BASE			((unsigned int)0x48000800U)
#define GPIOD_BASE			((unsigned int)0x48000C00U)
#define GPIOE_BASE			((unsigned int)0x48001000U)
#define GPIOF_BASE			((unsigned int)0x48001400U)
#define GPIOA				((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC				((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE				((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF				((GPIO_TypeDef*)GPIOF_BASE)

/*GPIO port mode register (GPIOx_MODER)*/
#define GPIO_PIN(y)						(y)
#define GPIO_MODER_MASK(y)				(3U<<(2*y))
#define GPIO_MODER_INPUT(y)				(0U<<(2*y))
#define GPIO_MODER_OUTPUT(y)			(1U<<(2*y))
#define GPIO_MODER_AF(y)				(2U<<(2*y))
#define GPIO_MODER_ANALOG(y)			(3U<<(2*y))

/*GPIO port output type register (GPIOx_OTYPER)*/
#define GPIO_OTYPER_MASK(y)				(1U<<(y))
#define GPIO_OTYPER_OUTPUT_PP(y)		(0U<<(y))
#define GPIO_OTYPER_OUTPUT_OD(y)		(1U<<(y))

/*GPIO port pull-up/pull-down register (GPIOx_PUPDR)*/
#define GPIO_PUPDR_MASK(y)				(3U<<(2*y))
#define GPIO_PUPDR_NO_PULL(y)			(0U<<(2*y))
#define GPIO_PUPDR_PULL_UP(y)			(1U<<(2*y))
#define GPIO_PUPDR_PULL_DOWN(y)			(2U<<(2*y))

/*GPIO port output data register (GPIOx_ODR)*/
#define GPIO_ODR_MASK(y)				(1U<<(y))
#define GPIO_ODR(y)						(1U<<(y))

/*GPIO port input data register (GPIOx_IDR)*/
#define GPIO_IDR_MASK(y)				(1U<<(y))

/*GPIO port output speed register (GPIOx_OSPEEDR)*/
#define GPIO_OSPEEDR_MASK(y)			(3U<<(2*y))
#define GPIO_OSPEEDR_LOW_SPEED(y)		(0U<<(2*y))
#define GPIO_OSPEEDR_MEDIUM_SPEED(y)	(1U<<(2*y))
#define GPIO_OSPEEDR_HIGH_SPEED(y)		(3U<<(2*y))

/*GPIO alternate function low register (GPIOx_AFRL)*/
#define GPIO_AFRL_MASK(y)				(15U<<((y*4))
#define GPIO_AFRL_AF0(y)				(0U<<((y*4))
#define GPIO_AFRL_AF1(y)				(1U<<((y*4))
#define GPIO_AFRL_AF2(y)				(2U<<((y*4))
#define GPIO_AFRL_AF3(y)				(3U<<((y*4))
#define GPIO_AFRL_AF4(y)				(4U<<((y*4))
#define GPIO_AFRL_AF5(y)				(5U<<((y*4))
#define GPIO_AFRL_AF6(y)				(6U<<((y*4))
#define GPIO_AFRL_AF7(y)				(7U<<((y*4))

/*GPIO alternate function high register (GPIOx_AFRH)*/
#define GPIO_AFRH_MASK(y)				(15U<<((y-8)*4))
#define GPIO_AFRH_AF0(y)				(0U<<((y-8)*4))
#define GPIO_AFRH_AF1(y)				(1U<<((y-8)*4))
#define GPIO_AFRH_AF2(y)				(2U<<((y-8)*4))
#define GPIO_AFRH_AF3(y)				(3U<<((y-8)*4))
#define GPIO_AFRH_AF4(y)				(4U<<((y-8)*4))
#define GPIO_AFRH_AF5(y)				(5U<<((y-8)*4))
#define GPIO_AFRH_AF6(y)				(6U<<((y-8)*4))
#define GPIO_AFRH_AF7(y)				(7U<<((y-8)*4))

/*GPIO port bit set/reset register (GPIOx_BSRR)*/
#define GPIO_BSRR_BS(y)					(1U<<y)
#define GPIO_BSRR_BR(y)					(1U<<(y+16))							

/*=======================RCC========================*/
#define RCC_BASE			((unsigned int)0x40021000U)
#define RCC					((RCC_TypeDef*)RCC_BASE)

/*AHB peripheral clock enable register (RCC_AHBENR)*/
#define GPIOA_CLOCK_EN			(1U<<17)
#define GPIOB_CLOCK_EN			(1U<<18)
#define GPIOC_CLOCK_EN			(1U<<19)
#define GPIOD_CLOCK_EN			(1U<<20)
#define GPIOE_CLOCK_EN			(1U<<21)
#define GPIOF_CLOCK_EN			(1U<<22)

/*APB peripheral clock enable register 2 (RCC_APB2ENR)*/
#define SYSCFG_CLOCK_EN			(1U<<0)

/*APB peripheral clock enable register 2 (RCC_APB2ENR)*/
#define USART1_CLOCK_EN			(1U<<14)

/*Clock control register (RCC_CR)*/
#define HSI_OSCILLATOR_ON		(1U<<0)
#define PLL_ENABLE				(1U<<24)
#define PLL_DISABLE				(~(1U<<24))
#define HSE_OSCILLATOR_ON		(1U<<16)


/*Bits 21:18 PLLMUL[3:0]: PLL multiplication factor*/
#define PLLMUL_MASK				(15U<<18)
#define PLLMUL2					(0U<<18)
#define PLLMUL3					(1U<<18)
#define PLLMUL4					(2U<<18)
#define PLLMUL5					(3U<<18)
#define PLLMUL6					(4U<<18)
#define PLLMUL7					(5U<<18)
#define PLLMUL8					(6U<<18)
#define PLLMUL9					(7U<<18)
#define PLLMUL10				(8U<<18)
#define PLLMUL11				(9U<<18)
#define PLLMUL12				(10U<<18)
#define PLLMUL13				(11U<<18)
#define PLLMUL14				(12U<<18)
#define PLLMUL15				(13U<<18)
#define PLLMUL16				(14U<<18)

/*CFGR: Bits 10:8 PPRE[2:0]: PCLK prescaler*/
#define HCLK_NODIV				(0U<<8)
#define HCLK_DIV2				(4U<<8)
#define HCLK_DIV4				(5U<<8)
#define HCLK_DIV8				(6U<<8)
#define HCLK_DIV16				(7U<<8)

/*CFGR: Bits 7:4 HPRE[3:0]: HCLK prescaler*/
#define SYSCLK_NODIV			(0U<<4)
#define SYSCLK_DIV2				(8U<<4)
#define SYSCLK_DIV4				(9U<<4)
#define SYSCLK_DIV8				(10U<<4)
#define SYSCLK_DIV16			(11U<<4)
#define SYSCLK_DIV64			(12U<<4)
#define SYSCLK_DIV128			(12U<<4)
#define SYSCLK_DIV256			(14U<<4)
#define SYSCLK_DIV512			(15U<<4)

/*CFGR: Bits 1:0 SW[1:0]: System clock switch*/
#define SYSCLK_SOURCE_HSI		(0U)
#define SYSCLK_SOURCE_HSE		(1U)
#define SYSCLK_SOURCE_PLL		(2U)
#define SYSCLK_SOURCE_HSI48		(3U)

/*CFGR3: Bits 1:0 USART1SW[1:0]: USART1 clock source selection*/
#define USART1_SOURCE_PCLK		(0U)
#define USART1_SOURCE_SYSCLK	(1U)
#define USART1_SOURCE_LSE		(2U)
#define USART1_SOURCE_HSI		(3U)

/*=======================NVIC=======================*/
#define NVIC_BASE			((unsigned int)0xE000E100U)
#define NVIC				((NVIC_TypeDef*)NVIC_BASE)

/*=======================SYSCFG=====================*/
#define SYSCFG_BASE			((unsigned int)0x40010000U)
#define SYSCFG				((SYSCFG_TypeDef*)SYSCFG_BASE)

/*y[3:0]*/
#define SYSCFG_EXTICR1_EXTI_MASK(y)		(15U<<(y*4))
#define SYSCFG_EXTICR1_EXTI_PA(y)		(0U<<(y*4))
#define SYSCFG_EXTICR1_EXTI_PB(y)		(1U<<(y*4))
#define SYSCFG_EXTICR1_EXTI_PC(y)		(2U<<(y*4))
#define SYSCFG_EXTICR1_EXTI_PD(y)		(3U<<(y*4))
#define SYSCFG_EXTICR1_EXTI_PE(y)		(4U<<(y*4))
#define SYSCFG_EXTICR1_EXTI_PF(y)		(5U<<(y*4))

/*=======================EXTI=======================*/
#define EXTI_BASE			((unsigned int)0x40010400U)
#define EXTI				((EXTI_TypeDef*)EXTI_BASE)

/*Interrupt mask register (EXTI_IMR)*/
#define EXTI_IMR_MASK(y)		(0U<<(y))
#define EXTI_IMR_NOT_MASK(y)	(1U<<(y))

/*Rising trigger selection register (EXTI_RTSR)*/
#define EXTI_RTSR_EN(y)			(1U<<(y))

/*Pending register (EXTI_PR)*/

/*=======================SYSTICK====================*/
#define STK_BASE			((unsigned int)0xE000E010U)
#define STK					((STK_TypeDef*)STK_BASE)

/*========================USART=====================*/
#define USART1_BASE			((unsigned int)0x40013800U)
#define USART2_BASE			((unsigned int)0x40004400U)
#define USART1				((USART_TypeDef*)USART1_BASE)
#define USART2				((USART_TypeDef*)USART2_BASE)

/*Control register 1 (USART_CR1)*/
#define USART_DIS					(~(1U<<0))		//UE = 0
#define USART_EN					(1U<<0)			//UE = 1
#define RECEIVER_EN					(1U<<2)			//RE = 1
#define TRANSMIT_EN					(1U<<3)			//TE = 1
#define RXNE_INTERRRUPT_EN			(1U<<5)			//RXNEIE
#define TRANS_INTERRUPT_EN			(1U<<6)			//TCIE
#define TRANS_DATA_REGISTER_EMPTY_IE	(1U<<7)		//TXEIE


#endif /*__HW_STM32F051R8_H__*/
