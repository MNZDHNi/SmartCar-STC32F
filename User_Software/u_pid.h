#ifndef __U_PID_H__
#define __U_PID_H__

typedef struct
{
	float speed_kp;
	float speed_ki;
	float speed_kd;
	
	float I_out;
	float P_out;
	float D_out;
	float MAX_Iout;
	float MAX_out;
	float out;
	
	float error[2];
	float feedback_value;
	float goal_value;
} MOTOR_PID;

void PID_Init(MOTOR_PID *motor_pid,const float pid_array[3],float max_out,float max_iout);
// float PID_LimitMax(float intput,float max);
float PID_Calculate(MOTOR_PID *Motor_pid,float get,float set);

#endif