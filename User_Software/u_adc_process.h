#ifndef __U_ADC_PROCESS_H__
#define __U_ADC_PROCESS_H__

// typedef struct {
//     unsigned int ADC_LH;
//     unsigned int ADC_RH;
//     unsigned int ADC_LV;
//     unsigned int ADC_RV;
// } ADC_VALUE;

#define MIN_SUM 0.0f
#define V_WEIGHT 0.3f

float u_adc_process(unsigned int (*adc_value)[5]);

#endif