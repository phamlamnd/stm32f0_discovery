#include "adc_driver.h"

static ADC_Type* const base = ADC_BASE_PTRS;

void ADC_DRV_EnableModule(void)
{
    /* Clear ready flag */
    REG_BIT_SET32(&(base->ISR), ADC_ISR_ADRDY(1U));
    /* Enable module */
    REG_BIT_SET32(&(base->CR), ADC_CR_ADEN(1U));
    while(((base->ISR) & ADC_ISR_ADRDY_MASK) == 0U)
    {
        /* Wait until ready flag set */
    }
}

void ADC_DRV_DisableModule(void)
{
    /* Stop ongoing conversion */
    REG_BIT_SET32(&(base->CR), ADC_CR_ADSTP(1U));
    while(((base->CR) & ADC_CR_ADSTP_MASK) != 0U)
    {
        /* Wait util ongoing conversion stop */
    }
    /* Disable module */
    REG_BIT_SET32(&(base->CR), ADC_CR_ADDIS(1U));
    while(((base->CR) & ADC_CR_ADEN_MASK) != 0)
    {
        /* Wait util ADEN = 0 */
    }
    /* Clear ready flag */
    REG_BIT_SET32(&(base->ISR), ADC_ISR_ADRDY(1U));
}

void ADC_DRV_EnableChannel(uint32_t channel)
{
    while((base->CR & ADC_CR_ADSTART_MASK) != 0U)
    {
        /* Wait conversion finish */
    }
    REG_BIT_SET32(&(base->CHSELR), (1U << channel));
    /* Enable internal channel */
    switch(channel)
    {
        case 16: /* temperature sensor */
            REG_BIT_SET32(&(base->CCR), (1U << 23));
            break;
        case 17: /* VREFINT internal voltage reference (bandgap) */
            REG_BIT_SET32(&(base->CCR), (1U << 22));
            break;
        case 18: /* VBAT */
            REG_BIT_SET32(&(base->CCR), (1U << 24));
            break;
        default:
            break;
    }
}

void ADC_DRV_DisableChannel(uint32_t channel)
{
    while((base->CR & ADC_CR_ADSTART_MASK) != 0U)
    {
        /* Wait conversion finish */
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
    config->clock        = ADC_CLOCK_CLK_MODE;
    config->sample       = ADC_SAMPLE_TIME_28_5_CLOCK_CYCLES;
    config->scan         = ADC_SCAN_UPWARD;
}

void ADC_DRV_ConfigConverter(const adc_cov_config_t * const config)
{
    uint32_t cfgr1 = 0u;
    uint32_t cfgr2 = 0u;
    uint32_t smpr  = 0u;
    switch(config->convMode)
    {
        case ADC_SINGLE_CONV_MODE:
            break;
        case ADC_CONTINUOUS_CONV_MODE:
            cfgr1 |= ADC_CFGR1_CONT(1U);
            break;
        case ADC_DISCONTINUOUS_CONV_MODE:
            cfgr1 |= ADC_CFGR1_DISCEN(1U);
            break;
        default:
            break;
    }  
    cfgr1 |= ADC_CFGR1_RES(config->resolution);
    cfgr1 |= ADC_CFGR1_OVRMOD(config->overwrite);
    cfgr1 |= ADC_CFGR1_ALIGN(config->align);
    cfgr1 |= ADC_CFGR1_EXTEN(config->edge);
    cfgr1 |= ADC_CFGR1_SCANDIR(config->scan);
    cfgr2 |= ADC_CFGR2_CKMODE(config->clock);
    smpr |= ADC_SMPR_SMP(config->sample);
    base->CFGR1 = cfgr1;
    base->CFGR2 = cfgr2;
    base->SMPR = smpr;
}

void ADC_DRV_StartConversion(void)
{
    REG_BIT_SET32(&(base->CR), ADC_CR_ADSTART(1U));
}

void ADC_DRV_StopConversion(void)
{
    REG_BIT_SET32(&(base->CR), ADC_CR_ADSTP(1U));
}

void ADC_DRV_EnableInterrupt(uint32_t mask)
{
    
}

void ADC_DRV_DisableInterrupt(uint32_t mask)
{
    
}

uint16_t ADC_DRV_GetConversionResult(void)
{
    uint16_t result = (uint16_t)(base->DR & ADC_DR_DATA_MASK);
    return result;
}

uint32_t ADC_DRV_GetStatusFlags(void)
{
    uint32_t flags = 0U;
    flags = (base->ISR);
    return flags;
}

void ADC_DRV_ClearStatusFlags(uint32_t mask)
{
    REG_BIT_SET32(&(base->ISR), mask);
}

status_t ADC_DRV_DoCalibaration(void)
{
    status_t ret = STATUS_ERROR;
    /* Check ADEN bit and DMAEN bit */
    if(((base->CR & ADC_CR_ADEN_MASK) == 0U) && ((base->CR & ADC_CFGR1_DMAEN_MASK) == 0U))
    {
        /* Start calibration */
        REG_BIT_SET32(&(base->CR), ADC_CR_ADCAL(1U));
        while(((base->CR) & ADC_CR_ADCAL_MASK) != 0U)
        {
            /* Wait until ADCAL = 0*/
        }
        ret = STATUS_SUCCESS;
    }
    return ret;
}

void ADC_DRV_SetTriggerSource(adc_trigger_source_t triggerSource)
{
    REG_BIT_SET32(&(base->CR), ADC_CFGR1_EXTSEL(triggerSource));
}
