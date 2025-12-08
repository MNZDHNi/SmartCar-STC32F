#ifndef __U_ENCODER_H__
#define __U_ENCODER_H__

#include "common.h"
#include "zf_tim.h"
#include "zf_gpio.h"

// 编码器结构体定义
typedef struct {
    volatile int32 pulse_count;   // 脉冲计数值（有符号，正反转）
    volatile int32 total_pulse;   // 总脉冲数（绝对值累加）
    volatile uint8 direction;     // 当前方向
    CTIMN_enum timer_ch;          // 计数器通道
    PIN_enum dir_pin;             // 方向引脚
} ENCODER_TypeDef;

// 编码器通道定义
#define LEFT_ENCODER    0
#define RIGHT_ENCODER   1

// 方向定义
#define DIR_FORWARD     0
#define DIR_REVERSE     1

// 函数声明
void encoder_init(void);
void encoder_get_data(uint8 encoder_id, int32 *pulse, int32 *total, uint8 *dir);
void encoder_reset(uint8 encoder_id);
void encoder_isr_timer3(void);
void encoder_isr_timer0(void);

#endif
