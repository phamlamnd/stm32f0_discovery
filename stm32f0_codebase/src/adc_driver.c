#include "adc_driver.h"

static ADC_Type* const base = ADC_BASE_PTRS;

void ADC_DRV_EnableModule(void)
{
    uint32_t mask = ADC_CR_ADEN_MASK | ADC_CR_ADDIS_MASK |
                    ADC_CR_ADSTART_MASK | ADC_CR_ADSTP_MASK |
                    ADC_CR_ADCAL_MASK;
    if((base->CR & mask) == 0U)
    {
        REG_BIT_SET32(&(base->CR), ADC_CR_ADEN(1));
    }
}

void ADC_DRV_DisableModule()
{
    if(((base->CR & ADC_CR_ADEN_MASK) != 0U) && ((base->CR & ADC_CR_ADSTART_MASK) == 0U))
    {
        REG_BIT_SET32(&(base->CR), ADC_CR_ADDIS(1));
    }
}

void ADC_DRV_EnableChannel(uint32_t channel)
{
    /* Wait conversion finish */
    while((base->CR & ADC_CR_ADSTART_MASK) != 0)
    {
    }
    REG_BIT_SET32(&(base->CHSELR), (1U << channel));
    //REG_BIT_SET32(&(base->CCR), (1U << 22));
    REG_BIT_SET32(&(base->CCR), (1U << 23));
    //REG_BIT_SET32(&(base->CCR), (1U << 24));
}

void ADC_DRV_DisableChannel(uint32_t channel)
{
    /* Wait conversion finish */
    while((base->CR & ADC_CR_ADSTART_MASK) != 0)
    {
    }
    REG_BIT_CLEAR32(&(base->CR), (1U << channel));
}

void ADC_DRV_GetDefaultConfigConverter(adc_cov_config_t * const config)
{
    config->convMode     = ADC_SINGLE_CONV_MODE;
    config->resolution   = ADC_DATA_RESOLUTION_12BITS;
    config->overwrite    = ADC_DATA_OVERWRITTEN;
    config->align        = ADC_DATA_RIGHT_ALIGNED;
    config->edge         = ADC_HARDWARE_TRIGGER_DISABLE;
}

void ADC_DRV_ConfigConverter(const adc_cov_config_t * const config)
{
    uint32_t cfgr1 = 0u;
    cfgr1 |= ADC_CFGR1_CONT(config->convMode);
    cfgr1 |= ADC_CFGR1_RES(config->resolution);
    cfgr1 |= ADC_CFGR1_OVRMOD(config->overwrite);
    cfgr1 |= ADC_CFGR1_ALIGN(config->align);
    cfgr1 |= ADC_CFGR1_EXTEN(config->edge);
    base->CFGR1 = cfgr1;
    
}

void ADC_DRV_StartConversion(void)
{
    REG_BIT_SET32(&(base->CR), ADC_CR_ADSTART(1U));
}

void ADC_DRV_StopConversion(void)
{
    
}

void ADC_DRV_EnableInterrupt(uint32_t mask)
{
    
}

void ADC_DRV_DisableInterrupt(uint32_t mask)
{
    
}

uint16_t ADC_DRV_GetConversionResult(uint32_t channel)
{
    uint16_t result = (uint16_t)(base->DR & ADC_CFGR1_DR_MASK);
    return result;
}

uint32_t ADC_DRV_GetStatusFlags(void)
{
    
}

void ADC_DRV_ClearStatusFlags(uint32_t mask)
{
    
}
