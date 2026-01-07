#include "u_adc.h"
#include "List.h"

#include "zf_adc.h"
#include "zf_gpio.h"

volatile float adc_value[4][5];
int MAX_default = 100;
List_5 list;

void U_ADC_Init(void)
{
    // GPIO init
    // 感觉不需要初始化GPIO，默认GPI_IMPEDANCE模式
    // gpio_pull_set(P0_6, NOPULL);
    // gpio_pull_set(P1_1, NOPULL);
    // gpio_pull_set(P1_5, NOPULL);
    // gpio_pull_set(P1_4, NOPULL);

    // gpio_mode(P0_6, GPI_IMPEDANCE);
    // gpio_mode(P1_1, GPI_IMPEDANCE);
    // gpio_mode(P1_5, GPI_IMPEDANCE);
    // gpio_mode(P1_4, GPI_IMPEDANCE);

    // ADC init
    adc_init(ADC_P06, ADC_SYSclk_DIV_16);
    adc_init(ADC_P11, ADC_SYSclk_DIV_16);
    adc_init(ADC_P15, ADC_SYSclk_DIV_16);
    adc_init(ADC_P14, ADC_SYSclk_DIV_16);

    List_5_Init(&list);
}

unsigned int ADC_get_MAX(ADCN_enum adcn)
{
    unsigned int adc_value = 0;
    char cnt = 0;
    unsigned int sum = 0;

    adc_value = adc_once(ADCN_enum adcn, ADC_12BIT);

    if(adc_value > MAX_default)
    {
        List_5_Append(&list, adc_value);
        cnt++;
        if(cnt >= 5)
        {
            MAX_default = List_5_Average(&list);
            cnt = 0;
        }
    }
    if(MAX_default > 4095)
    {
        MAX_default = 4095;
    }
    return adc_value;
}

float ADC_to_one(ADC_enum adcn)
{
    float adc_value = 0;

    adc_value = ADC_get_MAX(adcn);
    adc_value = (adc_value / MAX_default) * 100.0;
    return adc_value;
}

void U_ADC_Read(void)
{
    // 这样读取的数据真的能被及时处理吗
    int i;

    for (i = 0; i < 5; i++)
    {
        adc_value[0][i] = ADC_to_one(ADC_P06);
        adc_value[1][i] = ADC_to_one(ADC_P11);
        adc_value[2][i] = ADC_to_one(ADC_P15);
        adc_value[3][i] = ADC_to_one(ADC_P14);
    }
}