#ifndef __U_ADC_H__
#define __U_ADC_H__

extern volatile float adc_value[4][5];

void U_ADC_Init(void);
void U_ADC_Read(void);

#endif
