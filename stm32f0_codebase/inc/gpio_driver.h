#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "hw_stm32f051r8.h"

typedef enum
{
    GPIO_MODE_INPUT             = 0U,       /*!< GPIO Input Mode */
    GPIO_MODE_OUTPUT            = 1U,       /*!< GPIO Output Mode */
    GPIO_MODE_FUNCTION          = 2U,       /*!< GPIO Function Mode */
    GPIO_MODE_ANALOG            = 3U        /*!< GPIO Analog Mode */
} gpio_pin_mode_t;

typedef enum
{
    GPIO_OUTPUT_PUSH_PULL       = 0U,       /*!< GPIO Output Push Pull */
    GPIO_OUTPUT_OPEN_DRAIN      = 1U        /*!< GPIO Output Open Drain */
} gpio_output_type_t;

typedef enum
{
    GPIO_OUTPUT_SPEED_LOW       = 0U,       /*!< GPIO Output Speed Low */
    GPIO_OUTPUT_SPEED_MEDIUM    = 1U,       /*!< GPIO Output Speed Medium */
    GPIO_OUTPUT_SPEED_HIGH      = 2U        /*!< GPIO Output Speed High */
} gpio_output_speed_t;

typedef enum
{
    GPIO_PULL_UP_MODE           = 0U,       /*!< GPIO Pull-up Mode */
    GPIO_PULL_DOWN_MODE         = 1U        /*!< GPIO Pull-down Mode */
} gpio_pull_mode_t;

typedef struct
{
    uint32_t             pin;               /*!< Pin number */       
    gpio_pin_mode_t      mode;              /*!< GPIO Pin Mode */
    gpio_output_type_t   type;              /*!< GPIO Output Type */
    gpio_output_speed_t  speed;             /*!< GPIO Output Speed mode*/
    gpio_pull_mode_t     pull;              /*!< GPIO Pull mode */
} gpio_config_t;

void GPIO_DRV_PinInit(GPIO_Type* const gpio, const gpio_config_t* const config);
void GPIO_DRV_SetPin(GPIO_Type* const gpio, const uint32_t pin);
void GPIO_DRV_ClearPin(GPIO_Type* const gpio, const uint32_t pin);
void GPIO_DRV_TogglePin(GPIO_Type* const gpio, const uint32_t pin);

#endif /*GPIO_DRIVER_H*/
