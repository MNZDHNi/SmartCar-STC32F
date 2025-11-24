#ifndef __ENCODER_H__
#define __ENCODER_H__

#define ENCODER_LEFT  0
#define ENCODER_RIGHT 1

extern int left_encoder;
extern int right_encoder;

void PWMB_Init();
void Encoder_Handle();

#endif