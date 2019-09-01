#ifndef STM32F051R8_H
#define STM32F051R8_H
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
#define     __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

#define     NULL    ((void*)0)

#define REG_READ32(address)               (*(volatile uint32_t*)(address))
#define REG_WRITE32(address, value)       ((*(volatile uint32_t*)(address)) = (uint32_t)(value))
#define REG_BIT_SET32(address, mask)      ((*(volatile uint32_t*)(address)) |= (uint32_t)(mask))
#define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32_t*)(address)) &= ((uint32_t)~((uint32_t)(mask))))

/*=======================I/O PIN======================*/
#define LD3_PIN 9       /*!< PC9 */
#define LD4_PIN 8       /*!< PC8 */
#define USER_BUTTON 0   /*!< PA0 */
#define PIN0    0u
#define PIN1    1u
#define PIN2    2u
#define PIN3    3u
#define PIN4    4u
#define PIN5    5u
#define PIN6    6u
#define PIN7    7u
#define PIN8    8u
#define PIN9    9u
#define PIN10   10u
#define PIN11   11u
#define PIN12   12u
#define PIN13   13u
#define PIN14   14u
#define PIN15   15u

typedef struct
{
    __IO uint32_t ISR;                  /*!< Interrupt and status register */
    __IO uint32_t IER;                  /*!< Interrupt enable register */
    __IO uint32_t CR;                   /*!< Control register */
    __IO uint32_t CFGR1;                /*!< Configuration register 1 */
    __IO uint32_t CFGR2;                /*!< Configuration register 2 */
    __IO uint32_t SMPR;                 /*!< Sampling time register */
         uint32_t RESERVED0[2];
    __IO uint32_t TR;                   /*!< Watchdog threshold register */
         uint32_t RESERVED1[1];
    __IO uint32_t CHSELR;               /*!< Channel selection register */
         uint32_t RESERVED2[5];          
    __I  uint32_t DR;                   /*!< Data register */
         uint32_t RESERVED3[177]; 
    __IO uint32_t CCR;                  /*!< Common configuration register */
} ADC_Type;

#define ADC_BASE                        (uint32_t)0x40012400u
#define ADC                             ((ADC_Type*)(ADC_BASE))
#define ADC_BASE_PTRS                   ADC

#define ADC_CR_ADEN_MASK                0x1u
#define ADC_CR_ADEN_SHIFT               0u
#define ADC_CR_ADEN(x)                  (((uint32_t)(((uint32_t)(x))<<ADC_CR_ADEN_SHIFT))&ADC_CR_ADEN_MASK)
#define ADC_CR_ADDIS_MASK               0x2u
#define ADC_CR_ADDIS_SHIFT              1u
#define ADC_CR_ADDIS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CR_ADDIS_SHIFT))&ADC_CR_ADDIS_MASK)
#define ADC_CR_ADSTART_MASK             0x4u
#define ADC_CR_ADSTART_SHIFT            2u
#define ADC_CR_ADSTART(x)               (((uint32_t)(((uint32_t)(x))<<ADC_CR_ADSTART_SHIFT))&ADC_CR_ADSTART_MASK)
#define ADC_CR_ADSTP_MASK               0x10u
#define ADC_CR_ADSTP_SHIFT              4u
#define ADC_CR_ADSTP(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CR_ADSTP_SHIFT))&ADC_CR_ADSTP_MASK)
#define ADC_CR_ADCAL_MASK               0x80000000u
#define ADC_CR_ADCAL_SHIFT              31u
#define ADC_CR_ADCAL(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CR_ADCAL_SHIFT))&ADC_CR_ADCAL_MASK)

#define ADC_CFGR1_DMAEN_MASK            0x1u
#define ADC_CFGR1_DMAEN_SHIFT           0u
#define ADC_CFGR1_DMAEN(x)              (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_DMAEN_SHIFT))&ADC_CFGR1_DMAEN_MASK)
#define ADC_CFGR1_RES_MASK              0x18u
#define ADC_CFGR1_RES_SHIFT             3u
#define ADC_CFGR1_RES(x)                (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_RES_SHIFT))&ADC_CFGR1_RES_MASK)
#define ADC_CFGR1_ALIGN_MASK            0x20u
#define ADC_CFGR1_ALIGN_SHIFT           5u
#define ADC_CFGR1_ALIGN(x)              (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_ALIGN_SHIFT))&ADC_CFGR1_ALIGN_MASK)
#define ADC_CFGR1_EXTEN_MASK            0xC00u
#define ADC_CFGR1_EXTEN_SHIFT           10u
#define ADC_CFGR1_EXTEN(x)              (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_EXTEN_SHIFT))&ADC_CFGR1_EXTEN_MASK)
#define ADC_CFGR1_OVRMOD_MASK           0x1000u
#define ADC_CFGR1_OVRMOD_SHIFT          12u
#define ADC_CFGR1_OVRMOD(x)             (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_OVRMOD_SHIFT))&ADC_CFGR1_OVRMOD_MASK)
#define ADC_CFGR1_CONT_MASK             0x2000u
#define ADC_CFGR1_CONT_SHIFT            13u
#define ADC_CFGR1_CONT(x)               (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_CONT_SHIFT))&ADC_CFGR1_CONT_MASK)

#define ADC_CFGR1_DR_MASK               0xFFFFu
#define ADC_CFGR1_DR_SHIFT              0u
#define ADC_CFGR1_DR(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CFGR1_DR_SHIFT))&ADC_CFGR1_DR_MASK)

typedef struct
{
    __IO uint32_t MODER;                /*!< GPIO port mode register */
    __IO uint32_t OTYPER;               /*!< GPIO port output type register */
    __IO uint32_t OSPEEDR;              /*!< GPIO port output speed register */
    __IO uint32_t PUPDR;                /*!< GPIO port pull-up/pull-down register */
    __IO uint32_t IDR;                  /*!< GPIO port input data register */
    __IO uint32_t ODR;                  /*!< GPIO port output data register */
    __IO uint32_t BSRR;                 /*!< GPIO port bit set/reset register */
    __IO uint32_t LCKR;                 /*!< GPIO port configuration lock register */
    __IO uint32_t AFRL;                 /*!< GPIO alternate function low register */
    __IO uint32_t AFRH;                 /*!< GPIO alternate function high register */
    __IO uint32_t BRR;                  /*!< GPIO port bit reset register */
} GPIO_TypeDef;

/*=======================GPIO=======================*/
#define GPIOA_BASE  (uint32_t)0x48000000U
#define GPIOB_BASE  (uint32_t)0x48000400U
#define GPIOC_BASE  (uint32_t)0x48000800U
#define GPIOD_BASE  (uint32_t)0x48000C00U
#define GPIOE_BASE  (uint32_t)0x48001000U
#define GPIOF_BASE  (uint32_t)0x48001400U
#define GPIOA       ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD       ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE       ((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF       ((GPIO_TypeDef*)GPIOF_BASE)

#define GPIO_MODER_MODER_MASK       0x3u
#define GPIO_MODER_MODER_WITH       2u
#define GPIO_MODER_MODER0_MASK      0x3u
#define GPIO_MODER_MODER0_SHIFT     0u
#define GPIO_MODER_MODER0(x)        (((uint32_t)(((uint32_t)(x))<<GPIO_MODER_MODER0_SHIFT))&GPIO_MODER_MODER0_MASK)
#define GPIO_OTYPER_OT_MASK         0x1u
#define GPIO_OTYPER_OT_WITH         1u
#define GPIO_OSPEEDR_OSPEEDR_MASK   0x3u
#define GPIO_OSPEEDR_OSPEEDR_WITH   2u
#define GPIO_PUPDR_PUPDR_MASK       0x3u
#define GPIO_PUPDR_PUPDR_WITH       2u


typedef struct
{
    __IO uint32_t CR;       /*!< Clock control register */
    __IO uint32_t CFGR;     /*!< Clock configuration register */
    __IO uint32_t CIR;      /*!< Clock interrupt register */
    __IO uint32_t APB2RSTR; /*!< APB2 peripheral reset register */
    __IO uint32_t APB1RSTR; /*!< APB1 peripheral reset register */
    __IO uint32_t AHBENR;   /*!< AHB Peripheral Clock enable register */
    __IO uint32_t APB2ENR;  /*!< APB2 peripheral clock enable register */
    __IO uint32_t APB1ENR;  /*!< APB1 peripheral clock enable register */
    __IO uint32_t BDCR;     /*!< Backup domain control register */
    __IO uint32_t CSR;      /*!< Control/status register */
    __IO uint32_t AHBRSTR;  /*!< AHB peripheral clock reset register */
    __IO uint32_t CFGR2;    /*!< Clock configuration register2 */
    __IO uint32_t CFGR3;    /*!< Clock configuration register3 */
    __IO uint32_t CR2;      /*!< Clock control register 2 */
} RCC_TypeDef;

#define RCC_BASE            (uint32_t)0x40021000U
#define RCC                 ((RCC_TypeDef*)RCC_BASE)

#define RCC_AHBENR_IOPAEN_MASK      0x20000u
#define RCC_AHBENR_IOPAEN_SHIFT     17u
#define RCC_AHBENR_IOPAEN(x)        (((uint32_t)(((uint32_t)(x))<<RCC_AHBENR_IOPAEN_SHIFT))&RCC_AHBENR_IOPAEN_MASK)
#define RCC_AHBENR_IOPBEN_MASK      0x40000u
#define RCC_AHBENR_IOPBEN_SHIFT     18u
#define RCC_AHBENR_IOPBEN(x)        (((uint32_t)(((uint32_t)(x))<<RCC_AHBENR_IOPBEN_SHIFT))&RCC_AHBENR_IOPBEN_MASK)
#define RCC_AHBENR_IOPCEN_MASK      0x80000u
#define RCC_AHBENR_IOPCEN_SHIFT     19u
#define RCC_AHBENR_IOPCEN(x)        (((uint32_t)(((uint32_t)(x))<<RCC_AHBENR_IOPCEN_SHIFT))&RCC_AHBENR_IOPCEN_MASK)

#define RCC_APB2ENR_ADCEN_MASK      0x200u
#define RCC_APB2ENR_ADCEN_SHIFT     9u
#define RCC_APB2ENR_ADCEN(x)        (((uint32_t)(((uint32_t)(x))<<RCC_APB2ENR_ADCEN_SHIFT))&RCC_APB2ENR_ADCEN_MASK)

#define HCLK_NODIV              0x0
#define HCLK_DIV2               0x4
#define HCLK_DIV4               0x5
#define HCLK_DIV8               0x6
#define HCLK_DIV16              0x7
#define SYSCLK_NODIV            0x0
#define SYSCLK_DIV2             0x8
#define SYSCLK_DIV4             0x9
#define SYSCLK_DIV8             0xA
#define SYSCLK_DIV16            0xB
#define SYSCLK_DIV64            0xC
#define SYSCLK_DIV128           0xD
#define SYSCLK_DIV256           0xE
#define SYSCLK_DIV512           0xF
#define SYSCLK_SOURCE_HSI       0x0
#define SYSCLK_SOURCE_HSE       0x1
#define SYSCLK_SOURCE_PLL       0x2
#define SYSCLK_SOURCE_HSI48     0x3

typedef struct
{
    __IO uint32_t ISER;             /*!< Interrupt Set-enable Register */
         uint32_t RESERVED0[31];
    __IO uint32_t ICER;             /*!< Interrupt Clear-enable Register */
         uint32_t RESERVED1[31];
    __IO uint32_t ISPR;             /*!< Interrupt Set-pending Register */
         uint32_t RESERVED2[31];
    __IO uint32_t ICPR;             /*!< Interrupt Clear-pending Register */
         uint32_t RESERVED3[95];
    __IO uint32_t IPR[8];           /*!< Interrupt Priority Registers */
} NVIC_TypeDef;

#define NVIC_BASE           (uint32_t)0xE000E100U
#define NVIC                ((NVIC_TypeDef*)NVIC_BASE)

typedef struct
{
    __IO uint32_t CFGR1;            /*!< SYSCFG configuration register 1 */
         uint32_t RESERVED0[1];
    __IO uint32_t EXTICR[4];        /*!< SYSCFG external interrupt configuration register 1-4 */
    __IO uint32_t CFGR2;            /*!< SYSCFG configuration register 2 */
} SYSCFG_TypeDef;

#define SYSCFG_BASE         (uint32_t)0x40010000U
#define SYSCFG              ((SYSCFG_TypeDef*)SYSCFG_BASE)

typedef struct
{
    __IO uint32_t IMR;      /*!< Interrupt mask register */
    __IO uint32_t EMR;      /*!< Event mask register */
    __IO uint32_t RTSR;     /*!< Rising trigger selection register */
    __IO uint32_t FTSR;     /*!< Falling trigger selection register */
    __IO uint32_t SWIER;    /*!< Software interrupt event register */
    __IO uint32_t PR;       /*!< Pending register */
} EXTI_TypeDef;

/*=======================EXTI=======================*/
#define EXTI_BASE           (uint32_t)0x40010400U
#define EXTI                ((EXTI_TypeDef*)EXTI_BASE)

typedef struct
{
    __IO uint32_t CSR;      /*!< RW, SysTick Control and Status Register */
    __IO uint32_t RVR;      /*!< RW, SysTick Reload Value Register */
    __IO uint32_t CVR;      /*!< RW, SysTick Current Value Register */
    __IO uint32_t CALIB;    /*!< RO, SysTick Calibration Value Register */
} STK_TypeDef;
/*=======================SYSTICK====================*/
#define STK_BASE            (uint32_t)0xE000E010U
#define STK                 ((STK_TypeDef*)STK_BASE)


typedef struct
{
    __IO uint32_t CR1;      /*!< Control register 1 */
    __IO uint32_t CR2;      /*!< Control register 2 */
    __IO uint32_t CR3;      /*!< Control register 3 */
    __IO uint32_t BRR;      /*!< Baud rate register */
    __IO uint32_t GTPR;     /*!< Guard time and prescaler register */
    __IO uint32_t RTOR;     /*!< Receiver timeout register */
    __IO uint32_t RQR;      /*!< Request register */
    __IO uint32_t ISR;      /*!< Interrupt and status register */
    __IO uint32_t ICR;      /*!< Interrupt flag clear register */
    __IO uint32_t RDR;      /*!< Receive data register */
    __IO uint32_t TDR;      /*!< Transmit data register */
} USART_TypeDef;
/*========================USART=====================*/
#define USART1_BASE             (uint32_t)0x40013800U
#define USART2_BASE             (uint32_t)0x40004400U
#define USART1                  ((USART_TypeDef*)USART1_BASE)
#define USART2                  ((USART_TypeDef*)USART2_BASE)
#define USART1_SOURCE_PCLK      0x0
#define USART1_SOURCE_SYSCLK    0x1
#define USART1_SOURCE_LSE       0x2
#define USART1_SOURCE_HSI       0x3


#endif /* STM32F051R8_H */
