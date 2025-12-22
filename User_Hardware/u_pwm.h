#ifndef __U_PWM_H__
#define __U_PWM_H__

typedef enum {
    PWM_DIR_LEFT = 0,
    PWM_DIR_RIGHT
} Direction_x;

typedef enum {
    PWM_DIR_FORWARD = 0,
    PWM_DIR_BACKWARD
} Direction_y;

void U_PWM_Init(void)
void U_PWM_SetDuty(unsigned long duty0, unsigned long duty1)

void U_Change_Dir(Direction_x x, Direction_y y);

#endif
