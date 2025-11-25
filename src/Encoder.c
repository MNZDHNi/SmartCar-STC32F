#include <STC32G.H>
#include "Encoder.h"

/*
    zuo_PWMB_5 P20
    zuo_PWMB_6 P21
    you PWMA_1 P00
    you PWMA_2 P54

    // you_PWMB_7 P22
    // you_PWMB_8 P23
*/

#define PWMB_PSCR (120 - 1)       // PWM预分频值

int left_encoder = 0;
int right_encoder = 0;

unsigned int left_count = 0;
unsigned int right_count = 0;

void GPIO_Init()
{
    EAXFR = 1;

    P1M0 &= 0xFE;
    P1M1 &= 0xFE; // P10 准双向口

    P2M0 &= 0xFC; // P20~P21 准双向口
    P2M1 &= 0xFC;

    P5M0 &= 0xCF; // P54 准双向口
    P5M1 &= 0xCF;
}

void PWMB_Init()
{
    EAXFR = 1;

    GPIO_Init();

    // PWMB_PSCRH = (unsigned char)(PWMB_PSCR >> 8);
    // PWMB_PSCRL = (unsigned char)(PWMB_PSCR);

    PWMB_CCER1 = 0x00; // 关闭通道
    // PWMB_CCER2 = 0x00;

    PWMB_CCMR1 |= 0xA1; // 边沿对齐模式 80滤波
    PWMB_CCMR2 |= 0xA1;
    // PWMB_CCMR3 |= 0xA1;
    // PWMB_CCMR4 |= 0xA1;

    PWMB_CCER1 |= 0x11; // 使能通道
    // PWMB_CCER2 |= 0x11;

    PWMB_SMCR |= 0x03; // 编码器模式3

    PWMB_IER |= 0x02; // 使能中断
    EA = 1; // 总中断使能

    PWMB_CR1 |= 0x01; // 使能计数器 
}

void Encoder_Handle(unsigned char encoder, unsigned char cnt_H, unsigned char cnt_L)
{
    unsigned int newcount = cnt_H * 256 + cnt_L;
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
    }
}
