#ifndef __U_PWM_H__
#define __U_PWM_H__

typedef enum {
    DIR_LEFT = 0,
    DIR_RIGHT
} Direction_x;

typedef enum {
    DIR_FORWARD = 0,
    DIR_BACKWARD
} Direction_y;

void U_PWM_Init(void)
void U_PWM_SetDuty(unsigned long duty0, unsigned long duty1)

void U_Change_Dir(Direction_x x, Direction_y y);

#endif
