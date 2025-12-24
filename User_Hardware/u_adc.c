#include "u_adc.h"

#include "zf_adc.h"
#include "zf_gpio.h"

volatile unsigned int adc_value[4];

void U_ADC_Init(void)
{
    // GPIO init
    // 感觉不需要初始化GPIO，默认GPI_IMPEDANCE模式
    gpio_pull_set(P0_6, NOPULL);
    gpio_pull_set(P1_1, NOPULL);
    gpio_pull_set(P1_5, NOPULL);
    gpio_pull_set(P1_4, NOPULL);

    gpio_mode(P0_6, GPI_IMPEDANCE);
    gpio_mode(P1_1, GPI_IMPEDANCE);
    gpio_mode(P1_5, GPI_IMPEDANCE);
    gpio_mode(P1_4, GPI_IMPEDANCE);

    // ADC init
    adc_init(ADC_P06, ADC_SYSclk_DIV_16);
    adc_init(ADC_P11, ADC_SYSclk_DIV_16);
    adc_init(ADC_P15, ADC_SYSclk_DIV_16);
    adc_init(ADC_P14, ADC_SYSclk_DIV_16);
}

void U_ADC_Read(void)
{
    // 这样读取的数据真的能被及时处理吗

    adc_value[0] = adc_once(ADC_P06, ADC_12BIT);
    adc_value[1] = adc_once(ADC_P11, ADC_12BIT);
    adc_value[2] = adc_once(ADC_P15, ADC_12BIT);
    adc_value[3] = adc_once(ADC_P14, ADC_12BIT);
}