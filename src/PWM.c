#include <STC32G.H>
#include "PWM.h"

// 定义PWM频率和占空比相关变量
#define PWM_FREQUENCY 10000  // 10kHz PWM频率
#define SYS_CLK 11059200L    // 系统时钟频率11.0592MHz

// 全局变量 - 周期，占空比
unsigned int pwm_period = SYS_CLK / PWM_FREQUENCY;
unsigned int duty_ch1 = 500;  // 通道1默认占空比
unsigned int duty_ch2 = 500;  // 通道2默认占空比

// 函数声明
void PWMA_Init(void);
void Set_PWM_Duty(unsigned char channel, unsigned int duty);

void PWMA_Init(void)
{
    
}

void Set_PWM_Duty(unsigned char channel, unsigned int duty)
{

}