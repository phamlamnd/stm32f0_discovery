#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
#include "hw_stm32f051r8.h"

typedef enum
{
    ADC_DATA_RESOLUTION_12BITS = 0u,
    ADC_DATA_RESOLUTION_10BITS = 1u,
    ADC_DATA_RESOLUTION_8BITS  = 2u,
    ADC_DATA_RESOLUTION_6BITS  = 3u
} adc_data_resolution_t;

typedef enum
{
    ADC_DATA_RIGHT_ALIGNED      = 0u,
    ADC_DATA_LEFT_ALIGNED       = 1u
} adc_data_aligned_t;

typedef enum
{
    ADC_SINGLE_CONV_MODE     = 0u,
    ADC_CONTINUOUS_CONV_MODE = 1u
} adc_conv_mode_t;

typedef enum
{
    ADC_HARDWARE_TRIGGER_DISABLE    = 0u,
    ADC_HARDWARE_TRIGGER_RISING     = 1u,
    ADC_HARDWARE_TRIGGER_FALLING    = 2u,
    ADC_HARDWARE_TRIGGER_BOTH       = 3u
} adc_trigger_edge_t;

typedef enum
{
    ADC_DATA_PRESERVED   = 0u,
    ADC_DATA_OVERWRITTEN = 1u
} adc_data_overwritten_t;

typedef struct
{
    adc_conv_mode_t         convMode;
    adc_data_resolution_t   resolution;
    adc_data_overwritten_t  overwrite;
    adc_data_aligned_t      align;
    adc_trigger_edge_t      edge;
} adc_cov_config_t;

void ADC_DRV_EnableModule(void);
void ADC_DRV_DisableModule(void);
void ADC_DRV_EnableChannel(uint32_t channel);
void ADC_DRV_DisableChannel(uint32_t channel);
void ADC_DRV_GetDefaultConfigConverter(adc_cov_config_t * const config);
void ADC_DRV_ConfigConverter(const adc_cov_config_t * const config);
void ADC_DRV_StartConversion(void);
void ADC_DRV_StopConversion(void);
void ADC_DRV_EnableInterrupt(uint32_t mask);
void ADC_DRV_DisableInterrupt(uint32_t mask);
uint16_t ADC_DRV_GetConversionResult(uint32_t channel);
uint32_t ADC_DRV_GetStatusFlags(void);
void ADC_DRV_ClearStatusFlags(uint32_t mask);



#endif /* ADC_DRIVER_H */