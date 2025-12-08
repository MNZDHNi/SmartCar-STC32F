#include "encoder.h"

#include "zf_tim.h"
#include "zf_gpio.h"
#include "board.h"

// 全局编码器实例
static ENCODER_TypeDef encoder_left, encoder_right;

// 上一次的计数值（用于计算增量）
static uint16_t left_last_count = 0;
static uint16_t right_last_count = 0;

void encoder_init(void)
{
    // 初始化左侧编码器
    encoder_left.timer_ch = CTIM3_P04;
    encoder_left.dir_pin = P5_3;
    encoder_left.pulse_count = 0;
    encoder_left.total_pulse = 0;
    encoder_left.direction = DIR_FORWARD;
    
    // 初始化右侧编码器
    encoder_right.timer_ch = CTIM0_P34;
    encoder_right.dir_pin = P3_5;
    encoder_right.pulse_count = 0;
    encoder_right.total_pulse = 0;
    encoder_right.direction = DIR_FORWARD;
    
    // 初始化方向引脚为输入
    gpio_mode(P5_3, GPI_IMPEDANCE);  // P53作为方向输入
    gpio_mode(P3_5, GPI_IMPEDANCE);  // P35作为方向输入
    
    // 配置上拉电阻
    gpio_pull_set(P5_3, PULLUP);
    gpio_pull_set(P3_5, PULLUP);
    
    // 初始化计数器为外部计数模式
    ctimer_count_init(CTIM3_P04);  // 左侧编码器计数器
    ctimer_count_init(CTIM0_P34);  // 右侧编码器计数器
    
    // 清除计数器初始值
    ctimer_count_clean(CTIM3_P04);
    ctimer_count_clean(CTIM0_P34);
    
    // 初始化上一次计数值
    left_last_count = 0;
    right_last_count = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取编码器数据
//  @param      encoder_id   编码器ID：LEFT_ENCODER或RIGHT_ENCODER
//  @param      pulse        脉冲计数值（有符号，正反转）
//  @param      total        总脉冲数（绝对值累加）
//  @param      dir          当前方向
//  @return     void
//  Sample usage:           int32_t pulse, total; uint8_t dir;
//                          encoder_get_data(LEFT_ENCODER, &pulse, &total, &dir);
//-------------------------------------------------------------------------------------------------------------------
void encoder_get_data(uint8 encoder_id, int32 *pulse, int32 *total, uint8 *dir)
{
    if(encoder_id == LEFT_ENCODER) {
        *pulse = encoder_left.pulse_count;
        *total = encoder_left.total_pulse;
        *dir = encoder_left.direction;
    } else if(encoder_id == RIGHT_ENCODER) {
        *pulse = encoder_right.pulse_count;
        *total = encoder_right.total_pulse;
        *dir = encoder_right.direction;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      重置编码器数据
//  @param      encoder_id   编码器ID：LEFT_ENCODER或RIGHT_ENCODER
//  @return     void
//  Sample usage:           encoder_reset(LEFT_ENCODER);
//-------------------------------------------------------------------------------------------------------------------
void encoder_reset(uint8 encoder_id)
{
    if(encoder_id == LEFT_ENCODER) {
        encoder_left.pulse_count = 0;
        encoder_left.total_pulse = 0;
        ctimer_count_clean(CTIM3_P04);
        left_last_count = 0;
    } else if(encoder_id == RIGHT_ENCODER) {
        encoder_right.pulse_count = 0;
        encoder_right.total_pulse = 0;
        ctimer_count_clean(CTIM0_P34);
        right_last_count = 0;
    }
}

void encoder_isr_timer3(void)
{
    uint16_t current_count, diff;
    
    // 读取当前计数值
    current_count = ctimer_count_read(CTIM3_P04);
    
    // 计算增量（处理计数器溢出）
    if(current_count >= left_last_count) {
        diff = current_count - left_last_count;
    } else {
        diff = 65535 - left_last_count + current_count + 1;
    }
    
    // 读取方向引脚
    encoder_left.direction = (P5 & (1 << 3)) ? DIR_REVERSE : DIR_FORWARD;
    
    // 更新脉冲计数（根据方向正负）
    if(encoder_left.direction == DIR_FORWARD) {
        encoder_left.pulse_count += diff;
    } else {
        encoder_left.pulse_count -= diff;
    }
    
    // 累加总脉冲数（绝对值）
    encoder_left.total_pulse += diff;
    
    // 保存当前计数值
    left_last_count = current_count;
    
    AUXINTIF &= ~0x02;  // 清定时器3中断标志
}

void encoder_isr_timer0(void)
{
    uint16_t current_count, diff;
    
    // 读取当前计数值
    current_count = ctimer_count_read(CTIM0_P34);
    
    // 计算增量（处理计数器溢出）
    if(current_count >= right_last_count) {
        diff = current_count - right_last_count;
    } else {
        diff = 65535 - right_last_count + current_count + 1;
    }
    
    // 读取方向引脚
    encoder_right.direction = (P3 & (1 << 5)) ? DIR_REVERSE : DIR_FORWARD;
    
    // 更新脉冲计数（根据方向正负）
    if(encoder_right.direction == DIR_FORWARD) {
        encoder_right.pulse_count += diff;
    } else {
        encoder_right.pulse_count -= diff;
    }
    
    // 累加总脉冲数（绝对值）
    encoder_right.total_pulse += diff;
    
    // 保存当前计数值
    right_last_count = current_count;
    
    TF0 = 0;  // 清定时器0中断标志
}
