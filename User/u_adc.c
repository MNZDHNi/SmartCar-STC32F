#include "u_adc.h"

#include "zf_adc.h"
#include "zf_gpio.h"

unsigned int adc_value[4];

// GPIO init

void U_ADC_Init(void)
{
    adc_init(ADC_P06, ADC_SYSclk_DIV_16);
    adc_init(ADC_P11, ADC_SYSclk_DIV_16);
    adc_init(ADC_P15, ADC_SYSclk_DIV_16);
    adc_init(ADC_P14, ADC_SYSclk_DIV_16);
}

void U_ADC_Read(void)
{
    adc_value[0] = adc_once(ADC_P06, ADC_12BIT);
    adc_value[1] = adc_once(ADC_P11, ADC_12BIT);
    adc_value[2] = adc_once(ADC_P15, ADC_12BIT);
    adc_value[3] = adc_once(ADC_P14, ADC_12BIT);
}