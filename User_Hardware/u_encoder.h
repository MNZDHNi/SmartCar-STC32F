#ifndef __U_ENCODER_H__
#define __U_ENCODER_H__

extern volatile long int left_count;
extern volatile long int right_count;

void u_encoder_init(void);
void u_encoder_open(void);
void u_left_encoder_P5_isr(void);
void u_right_encoder_P3_isr(void);

#endif
