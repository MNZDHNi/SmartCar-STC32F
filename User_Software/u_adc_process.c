#include "u_adc_process.h"

#include "u_adc.h"

float u_adc_process(int* p)
{
    float diff = (float)(p[1] - p[2]);
    float sum = (float)(p[1] + p[2]);
    float v_diff = (float)(p[0] - p[3]);
    float v_sum = (float)(p[0] + p[3]);
    float result = 0.0f;

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