#include <STC32G.H>
#include "interrupts.h"
#include "Encoder.h"

// PWMB编码器中断服务程序
void PWMB_Routine() interrupt 27
{
    unsigned char cnt_H, cnt_L;
    if(PWMB_SR1 & 0x02)
    {
        cnt_H = PWMB_CCR5H;
        cnt_L = PWMB_CCR5L;

        PWMB_SR1 &= ~0x02; // 清除中断标志位

        Encoder_Handle(ENCODER_LEFT);
    }
    else if(PWMB_SR1 & 0x08)
    {
        cnt_H = PWMB_CCR7H;
        cnt_L = PWMB_CCR7L;

        PWMB_SR1 &= ~0x08; // 清除中断标志位

        Encoder_Handle(ENCODER_RIGHT);
    }
}