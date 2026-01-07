#include "u_adc.h"
#include "List.h"

#include "zf_adc.h"
#include "zf_gpio.h"

volatile unsigned int adc_value[4][5];
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

void ADC_get_MAX(ADCN_enum adcn)
{
    adc_once(ADCN_enum adcn, ADC_12BIT);
}

void ADC_to_one()
{

}

void U_ADC_Read(void)
{
    // 这样读取的数据真的能被及时处理吗
    int i;

    for (i = 0; i < 5; i++)
    {
        adc_value[0][i] = adc_once(ADC_P06, ADC_12BIT);
        adc_value[1][i] = adc_once(ADC_P11, ADC_12BIT);
        adc_value[2][i] = adc_once(ADC_P15, ADC_12BIT);
        adc_value[3][i] = adc_once(ADC_P14, ADC_12BIT);
    }

    // 对数据归一化后放入adc_value数组前
}