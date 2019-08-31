#include "tm1637_driver.h"

static void delay_us(unsigned char us)
{
    unsigned char i;
    for(i = 0; i < us; i++)
    {
        asm("nop");
    }
}

static void I2C_Start(void) // 1637 start
{
    GPIOB->ODR |= 0x01<<8; //CLK = 1
    GPIOB->ODR |= 0x01<<9; //DIO = 1
    delay_us(2);
    GPIOB->ODR &= ~(0x01<<9); //DIO = 0
}

static void I2C_Ask(void) // 1637 Answer
{
    GPIOB->ODR &= ~(0x01<<8); //CLK = 0
    delay_us(5); // After the falling edge of the eighth clock delay 5us, ACK signals the beginning of judgment
    GPIOB->MODER &= ~(0x03<<18);
    GPIOB->PUPDR &= ~(0x03<<18);
    GPIOB->PUPDR |= 0x01<<18;
    while (GPIOB->IDR&(0x01<<9)); //DIO
    GPIOB->MODER &= ~(0x03<<18);
    GPIOB->MODER |= 0x01<<18;
    GPIOB->OTYPER &= ~(0x01<<9);
    GPIOB->ODR |= 0x01<<8; //CLK = 1
    delay_us(2);
    GPIOB->ODR &= ~(0x01<<8); //CLK = 0
}

static void I2C_Stop(void) // 1637 Stop
{
    GPIOB->ODR &= ~(0x01<<8); //CLK = 0
    delay_us(2);
    GPIOB->ODR &= ~(0x01<<9); //DIO = 0
    delay_us(2);
    GPIOB->ODR |= 0x01<<8; //CLK = 1
    delay_us(2);
    GPIOB->ODR |= 0x01<<9; //DIO = 1
}

static void I2C_WrByte(unsigned char oneByte) // write a byte
{
    unsigned char i;
    for (i = 0; i <8; i++)
    {
        GPIOB->ODR &= ~(0x01<<8); //CLK = 0
        if (oneByte & 0x01) // low front
        {
            GPIOB->ODR |= 0x01<<9; //DIO = 1
        }
        else
        {
            GPIOB->ODR &= ~(0x01<<9); //DIO = 0
        }
        delay_us(3);
        oneByte = oneByte>>1;
        GPIOB->ODR |= 0x01<<8; //CLK = 1
        delay_us(3);
    }
}

void TM1637_DRV_Init(void)	//CLK:PB8, DIO:PB9
{
    RCC->AHBENR |= 0x01<<18;	//Enable clock GPIOB
    GPIOB->MODER &= ~(0x03<<16);
    GPIOB->MODER |= 0x01<<16;
    GPIOB->OTYPER &= ~(0x01<<8);

    GPIOB->MODER &= ~(0x03<<18);
    GPIOB->MODER |= 0x01<<18;
    GPIOB->OTYPER &= ~(0x01<<9);

    GPIOB->ODR &= ~(0x01<<8); //CLK LOW LEVEL
    GPIOB->ODR &= ~(0x01<<9); //DIO LOW LEVEL
}
static unsigned int dot = 1;
static const char segmentMap[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0-9

void TM1637_DRV_Display(unsigned char digit4, unsigned char digit3,
                        unsigned char digit2, unsigned char digit1)
{
    unsigned int num = 5673;
    I2C_Start();
    I2C_WrByte(0x40); //40H address is automatically incremented by 1 mode, 44H fixed address mode
    I2C_Ask();
    I2C_Stop();

    I2C_Start();
    I2C_WrByte(0xc0); // Set the first address
    I2C_Ask();

    I2C_WrByte(segmentMap[digit4]); // Send data
    I2C_Ask();
    if(dot == 1)
    {
        I2C_WrByte(segmentMap[digit3] | 0x80);
        dot = 0;
    }
    else
    {
        I2C_WrByte(segmentMap[digit3]);
        dot = 0;
    }

    I2C_Ask();
    I2C_WrByte(segmentMap[digit2]);
    I2C_Ask();
    I2C_WrByte(segmentMap[digit1]);
    I2C_Ask();
    I2C_Stop();

    I2C_Start();
    I2C_WrByte(0x89); // Open display, maximum brightness
    I2C_Ask();
    I2C_Stop();
}