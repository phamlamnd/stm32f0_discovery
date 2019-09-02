#include "tm1637_driver.h"
#include "gpio_driver.h"
#include "clock_driver.h"

static void delay_us(uint8_t us)
{
    uint8_t i;
    for(i = 0; i < us; i++)
    {
        asm("nop");
    }
}

static void I2C_Start(void) // 1637 start
{
    GPIO_DRV_SetPin(GPIOB, PIN8); //CLK = 1
    GPIO_DRV_SetPin(GPIOB, PIN9); //DIO = 1
    delay_us(2);
    GPIO_DRV_ClearPin(GPIOB, PIN9); //DIO = 0
}

static void I2C_Ask(void) // 1637 Answer
{
    GPIO_DRV_ClearPin(GPIOB, PIN8); //CLK = 0
    delay_us(5); // After the falling edge of the eighth clock delay 5us, ACK signals the beginning of judgment
    gpio_config_t dio_pin_config = {
        .pin    = 9,
        .mode   = GPIO_MODE_INPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    GPIO_DRV_PinInit(GPIOB, &dio_pin_config);
    while (GPIOB->IDR&(0x01<<9)) //DIO
    {
    }
    dio_pin_config.mode = GPIO_MODE_OUTPUT;
    GPIO_DRV_PinInit(GPIOB, &dio_pin_config);
    GPIO_DRV_SetPin(GPIOB, PIN8); //CLK = 1
    delay_us(2);
    GPIO_DRV_ClearPin(GPIOB, PIN8); //CLK = 0
}

static void I2C_Stop(void) // 1637 Stop
{
    GPIO_DRV_ClearPin(GPIOB, PIN8); //CLK = 0
    delay_us(2);
    GPIO_DRV_ClearPin(GPIOB, PIN9); //DIO = 0
    delay_us(2);
    GPIO_DRV_SetPin(GPIOB, PIN8); //CLK = 1
    delay_us(2);
    GPIO_DRV_ClearPin(GPIOB, PIN9); //DIO = 1
}

static void I2C_WrByte(uint8_t oneByte) // write a byte
{
    uint8_t i;
    for (i = 0; i <8; i++)
    {
        GPIO_DRV_ClearPin(GPIOB, PIN8);   //CLK = 0
        if (oneByte & 0x01)            // low front
        {
            GPIO_DRV_SetPin(GPIOB, PIN9); //DIO = 1   
        }
        else
        {
            GPIO_DRV_ClearPin(GPIOB, PIN9); //DIO = 0
        }
        delay_us(3);
        oneByte = oneByte>>1;
        GPIO_DRV_SetPin(GPIOB, PIN8);      //CLK = 1
        delay_us(3);
    }
}

void TM1637_DRV_Config()	//CLK:PB8, DIO:PB9
{
    /* Select CLK and DIO pin for TM1637 */
    gpio_config_t clk_pin_config = {
        .pin    = 8,
        .mode   = GPIO_MODE_OUTPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    gpio_config_t dio_pin_config = {
        .pin    = 9,
        .mode   = GPIO_MODE_OUTPUT,
        .type   = GPIO_OUTPUT_PUSH_PULL,
        .speed  = GPIO_OUTPUT_SPEED_LOW,
        .pull   = GPIO_PULL_DOWN_MODE
    };
    CLOCK_DRV_Enable(CLOCK_PORTB);
    GPIO_DRV_PinInit(GPIOB, &clk_pin_config);
    GPIO_DRV_PinInit(GPIOB, &dio_pin_config);
    CLOCK_DRV_Enable(CLOCK_PORTB);
    GPIO_DRV_ClearPin(GPIOB, PIN8);
    GPIO_DRV_ClearPin(GPIOB, PIN9);
}

static const uint8_t segmentMap[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0-9
void TM1637_DRV_Display(tm1637_display_mode_t mode, tm1637_digit_t digit)
{
    I2C_Start();
    I2C_WrByte(0x40); //40H address is automatically incremented by 1 mode, 44H fixed address mode
    I2C_Ask();
    I2C_Stop();

    I2C_Start();
    I2C_WrByte(0xc0); // Set the first address
    I2C_Ask();

    I2C_WrByte(segmentMap[digit.digit4]); // Send data
    I2C_Ask();
    if(mode == TM1637_CLOCK_MODE)
    {
        I2C_WrByte(segmentMap[digit.digit3] | 0x80);
    }
    else
    {
        I2C_WrByte(segmentMap[digit.digit3]);
    }

    I2C_Ask();
    I2C_WrByte(segmentMap[digit.digit2]);
    I2C_Ask();
    I2C_WrByte(segmentMap[digit.digit1]);
    I2C_Ask();
    I2C_Stop();

    I2C_Start();
    I2C_WrByte(0x89); // Open display, maximum brightness
    I2C_Ask();
    I2C_Stop();
}