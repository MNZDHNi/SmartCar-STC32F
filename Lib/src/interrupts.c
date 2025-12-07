#include <STC32G.H>
#include "interrupts.h"
#include "Encoder.h"

// PWMA编码器中断服务程序
void PWMA_Routine() interrupt 26
{
    unsigned char cnt_H, cnt_L;
    if(PWMA_SR1 & 0x02)
    {
        cnt_H = PWMA_CCR1H;
        cnt_L = PWMA_CCR1L;

        PWMA_SR1 &= ~0x02; // 清除中断标志位

        Encoder_Handle(ENCODER_RIGHT, cnt_H, cnt_L);
    }
}

// PWMB编码器中断服务程序
void PWMB_Routine() interrupt 27
{
    unsigned char cnt_H, cnt_L;
    if(PWMB_SR1 & 0x02)
    {
        cnt_H = PWMB_CCR5H;
        cnt_L = PWMB_CCR5L;

        PWMB_SR1 &= ~0x02; // 清除中断标志位

        Encoder_Handle(ENCODER_LEFT, cnt_H, cnt_L);
    }
}
