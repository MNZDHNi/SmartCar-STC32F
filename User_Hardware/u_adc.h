#ifndef __U_ADC_H__
#define __U_ADC_H__

extern volatile unsigned int adc_value[4];

void U_ADC_Init(void);
void U_ADC_Read(void);

#endif
