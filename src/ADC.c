#include <STC32G.H>
#include "ADC.h"

void GPIO_ADC_Init(void)
{
    /*
        左水平 P06
        左竖直 P11
        右竖直 P15
        右水平 P14
    */
    // init P06, P11, P14, P15 high
    // 默认高阻输入，无需初始化
    EAXFR = 1;

    P0M1 &= 0x40;
    P0M0 &= 0x00;
    P1M1 &= 0x32;
    P1M0 &= 0x00;
}

void ADC_Init(void)
{
    GPIO_ADC_Init();

    EAXFR = 1;

    ADCTIM = 0x3F;
    ADCCFG = 0x1F;

    ADC_CONTR = 0x80;   // enable ADC
}

unsigned int ADC_Read(unsigned char position)
{
    ADC_CONTR |= position;        // 启动转换
    while (!(ADC_CONTR & 0x20)); // 等待转换完成
    ADC_CONTR &= ~0x20;       // 清除完成标志
    return (ADC_RES << 8) | ADC_RESL; // 组合 12 位结果
}

void ADC_Read_All()
{
    unsigned int left_x = ADC_Read(0x0E);
    unsigned int left_y = ADC_Read(0x01);
    unsigned int right_x = ADC_Read(0x04);
    unsigned int right_y = ADC_Read(0x05);
}
