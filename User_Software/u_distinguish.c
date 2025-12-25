#include "u_distinguish.h" 
#include "u_adc.h"
#include "u_adc_process.h"

#define MIN_SIGNAL_THRESH     // 有效信号最小阈值
#define STRAIGHT_THRESH       // 直道左右差值阈值
#define CURVE_THRESH          // 弯道左右差值阈值
#define CROSS_THRESH          // 交叉道信号阈值

float u_adc_process(int* p);

int STRAIGHT(int value) {

    float STRAIGHT_CAL=u_adc_process(adc_value);
    if(STRAIGHT_CAL<MIN_SIGNAL_THRESH&&STRAIGHT_CAL>STRAIGHT_THRESH)return 1;
    else return 0;
}
int Curve(int value) {
    float STRAIGHT_CAL=u_adc_process(adc_value);
    if(STRAIGHT_CAL > CURVE_THRESH)return 1;
    else return 0;
}
