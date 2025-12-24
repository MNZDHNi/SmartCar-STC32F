#include "u_encoder.h"

#include "zf_tim.h"
#include "zf_gpio.h"

volatile long int left_count = 0;
volatile long int right_count = 0;

unsigned int lest_left_count = 0;
unsigned int lest_right_count = 0;

void u_encoder_init()
{
    left_count = 0;
    right_count = 0;

    // IO 中断模式配置
    gpio_mode(P5_3, GPI_IMPEDANCE); // 左编码器
    gpio_mode(P3_5, GPI_IMPEDANCE); // 左编码器

    EAXFR = 1;

    P5IM0 |= (1 << 3); // P5.3 上升沿中断
    P3IM0 |= (1 << 5); // P3.5 

    PINIPH |= (1 << 3); // P3 P5 3优先级
    PINIPL |= (1 << 3);
    PINIPH |= (1 << 5);
    PINIPL |= (1 << 5);

    P3INTE |= (1 << 5); // P3.5 中断使能
    P5INTE |= (1 << 3); // P5.3

    // 定时器配置
    ctimer_count_init(CTIM3_P04); // 左编码器
    ctimer_count_init(CTIM0_P34); // 右编码器

    ET0 = 1;    // 计数器溢出中断
    ET3 = 1;

    // 定时器中断优先级记得修改
}

void u_encoder_open(void)
{
    EAXFR = 1;
    EA = 1;
}

void u_left_encoder_P5_isr(void)
{
    char current_A = P53;
    unsigned int current_left_count = ctimer_count_read(CTIM3_P04);

    if(current_A)
    {
        left_count += (current_left_count > lest_left_count) ? (current_left_count - lest_left_count) : (0xFFFF - lest_left_count + current_left_count);
    }
    else
    {
        left_count -= (current_left_count > lest_left_count) ? (current_left_count - lest_left_count) : (0xFFFF - lest_left_count + current_left_count);
    }

    lest_left_count = current_left_count;
}

void u_right_encoder_P3_isr(void)
{
    char current_A = P35;
    unsigned int current_right_count = ctimer_count_read(CTIM0_P34);

    if(current_A)
    {
        right_count += (current_right_count > lest_right_count) ? (current_right_count - lest_right_count) : (0xFFFF - lest_right_count + current_right_count);
    }
    else
    {
        right_count -= (current_right_count > lest_right_count) ? (current_right_count - lest_right_count) : (0xFFFF - lest_right_count + current_right_count);
    }
    lest_right_count = current_right_count;
}

/*
void u_left_encoder_timer3_isr(void)
{
    
}

void u_right_encoder_timer0_isr(void)
{
    
}
*/