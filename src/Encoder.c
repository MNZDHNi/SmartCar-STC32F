#include <STC32G.H>
#include "Encoder.h"

/*
    zuo_PWMB_5 P20
    zuo_PWMB_6 P21
    zuo_PWMB_7 P22
    zuo_PWMB_8 P23
*/

int left_encoder = 0;
int right_encoder = 0;

unsigned int left_count = 0;
unsigned int right_count = 0;

void PWMB_Init()
{
    EAXFR = 1;

    PWMB_CCER1 = 0x00; // 关闭通道
    PWMB_CCER2 = 0x00;

    PWMB_CCMR1 |= 0xA1; // 边沿对齐模式 80滤波
    PWMB_CCMR2 |= 0xA1;
    PWMB_CCMR3 |= 0xA1;
    PWMB_CCMR4 |= 0xA1;

    PWMB_CCER1 |= 0x11; // 使能通道
    PWMB_CCER2 |= 0x11;

    PWMB_SMCR |= 0x03; // 编码器模式3

    PWMB_IER |= 0x0A; // 使能中断
    PWMB_CR1 |= 0x01; // 使能计数器 
}

void Encoder_Handle(unsigned char encoder)
{
    newcount = cnt_H * 256 + cnt_L;
    switch(encoder)
    {
        case ENCODER_LEFT:
            if(newcount < left_count)
            {
                left_encoder--;
            }
            else if(newcount > left_count)
            {
                left_encoder++;
            }
            left_count = newcount;
            break;

        case ENCODER_RIGHT:
            if(newcount < right_count)
            {
                right_encoder--;
            }
            else if(newcount > right_count)
            {
                right_encoder++;
            }
            right_count = newcount;
            break;

        case default:
            break;
    }
}