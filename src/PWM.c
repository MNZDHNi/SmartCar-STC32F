#include <STC32G.H>
#include "PWM.h"

/*
    ch1 zuo_pwm 2.4
    ch2 you_pwm 2.6
*/

#define PWMA_PSCR (120 - 1)       // PWM预分频值
#define SYS_CLK 11059200L    // 系统时钟频率11.0592MHz

// 全局变量 - 周期，占空比
unsigned int pwm_period = 2000;
unsigned int duty_ch1 = 1000;  // 通道1默认占空比
unsigned int duty_ch2 = 1000;  // 通道2默认占空比

// 函数声明
void PWMA_Init(void);
void Set_PWM_Duty(unsigned char channel, unsigned int duty);

void PWMA_Init(void)
{
    EAXFR = 1;

    P2M0 |= 0x50;  // 设置P2.4和P2.6为推挽输出
    P2M1 |= 0x00;

    PWMA_PS |= 0x50; //切换到 P2.4 P2.6 作为 PWM 输出

    //预分频
    PWMA_PSCRH = (unsigned char)(PWMA_PSCR >> 8);
    PWMA_PSCRL = (unsigned char)(PWMA_PSCR);

    PWMA_CCER2 = 0x00;
    PWMA_CCMR3 |= 0x60; //PWM1 置为 PWM 模式 1
    PWMA_CCMR4 |= 0x60; //PWM2 置为 PWM 模式 1

    PWMA_CCER2 |= 0x11; //使能 PWM1 和 PWM2 输出

    PWMA_CCR3H = (unsigned char)(duty_ch1 >> 8);
    PWMA_CCR3L = (unsigned char)(duty_ch1);
    PWMA_CCR4H = (unsigned char)(duty_ch2 >> 8);
    PWMA_CCR4L = (unsigned char)(duty_ch2);

    PWMA_ARRH = (unsigned char)(pwm_period >> 8);
    PWMA_ARRL = (unsigned char)(pwm_period);

    PWMA_ENO |= 0x50; //使能 PWMA3P 和 PWMA4P
    PWMA_BKR |= 0x80; //主输出使能

    PWMA_CR1 |= 0x01; //使能计数器
}

void Set_PWM_Duty(unsigned char channel, unsigned int duty)
{
    if(duty <= 2000)
    {
        switch(channel)
        {
            case 1:
                duty_ch1 = duty;
                PWMA_CCR3H = (unsigned char)(duty_ch1 >> 8);
                PWMA_CCR3L = (unsigned char)(duty_ch1);
                break;
            case 2:
                duty_ch2 = duty;
                PWMA_CCR4H = (unsigned char)(duty_ch2 >> 8);
                PWMA_CCR4L = (unsigned char)(duty_ch2);
                break;
            default:
                // 无效通道
                break;
        }
    }
}