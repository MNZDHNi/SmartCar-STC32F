#include "u_adc_process.h"

void u_adc_filter(float (*adc_value)[5], float* adc_value_filter)
{
    int i, j;
    float max_value = 0;
    float min_value = 100;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 5; j++)
        {
            adc_value_filter[i] = 0;

            if(adc_value[i][j] > max_value)
            {
                max_value = adc_value[i][j];
            }
            if(adc_value[i][j] < min_value)
            {
                min_value = adc_value[i][j];
            }
            adc_value_filter[i] += adc_value[i][j];
        }
        adc_value_filter[i] = adc_value_filter[i] - max_value - min_value;
        adc_value_filter[i] = adc_value_filter[i] / 3;

        max_value = 0;
        min_value = 100;
    }
}


float u_adc_process(float (*adc_value)[5])
{
    float adc_value_filter[4] = {0, 0, 0, 0};
    float diff, sum, v_diff, v_sum, result;

    u_adc_filter(adc_value, adc_value_filter);

    diff = (float)(adc_value_filter[1] - adc_value_filter[2]);
    sum = (float)(adc_value_filter[1] + adc_value_filter[2]);
    v_diff = (float)(adc_value_filter[0] - adc_value_filter[3]);
    v_sum = (float)(adc_value_filter[0] + adc_value_filter[3]);
    result = 0.0f;

    if(sum < MIN_SUM)
    {
        return 0.0f;
    }
    
    result = diff / sum;

    if(v_sum < MIN_SUM)
    {
        return result;
    }

    result = result * (1.0f - V_WEIGHT) + v_diff / v_sum * V_WEIGHT;
    return result;
}