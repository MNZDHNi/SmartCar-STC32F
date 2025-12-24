#include "u_pwm.h"

#include "zf_pwm.h"
#include "zf_gpio.h"

void U_PWM_Init(void)
{
    pwm_init(PWMA_CH3P_P24, 1000, 0); // 初始化PWM，频率1000Hz，占空比0%
    pwm_init(PWMA_CH4P_P26, 1000, 0);

    gpio_mode(P1_0, GPO_PP); // 设置P1.0 P1.3为推挽输出模式
    gpio_mode(P1_3, GPO_PP);

    P10 = 0; // 初始化P1.0和P1.3为低电平
    P13 = 0;
}

void U_PWM_SetDuty(unsigned long duty0, unsigned long duty1)
{
    if(duty0 <= 10000 && duty1 <= 10000) // 占空比范围0~10000，对应0%~100%
    {
    pwm_duty(PWMA_CH3P_P24, duty0); // 设置PWM占空比
    pwm_duty(PWMA_CH4P_P26, duty1);
    }
}

void U_Change_Dir(Direction_x x, Direction_y y)
{
    if (x == DIR_LEFT)
    {
        P10 = y;
    }
    else if(x == DIR_RIGHT) 
    {
        P13 = y;
    }
}
