#include "headfile.h"

#include "encoder.h"

// 定时器0中断服务程序
void timer0_isr(void) interrupt 1
{
    u_encoder_isr_timer0();  // 处理右侧编码器
}

// 定时器3中断服务程序
void timer3_isr(void) interrupt 19
{
    u_encoder_isr_timer3();  // 处理左侧编码器
}