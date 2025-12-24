#include "headfile.h"

#include "u_encoder.h"

// // 定时器中断服务程序
// void timer0_isr(void) interrupt 1
// {
//     // 处理正向溢出
// }

// void timer3_isr(void) interrupt 19
// {
//     // 处理正向溢出
// }

// IO口中断服务程序
void P3_ISR(void) interrupt 0
{
    u_right_encoder_P3_isr();
}

void P5_ISR(void) interrupt 2
{
    u_left_encoder_P5_isr();
}