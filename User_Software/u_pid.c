#include "u_pid.h"

void PID_Init(MOTOR_PID *motor_pid,const float pid_array[3],float max_out,float max_iout)
{
	motor_pid->speed_kp = pid_array[0];
	motor_pid->speed_ki = pid_array[1];
	motor_pid->speed_kd = pid_array[2];

	motor_pid->P_out = 0;
	motor_pid->I_out = 0;
	motor_pid->D_out = 0;

	motor_pid->MAX_Iout = max_iout;
	motor_pid->MAX_out = max_out;

	motor_pid->out = 0;
	motor_pid->feedback_value = 0;
	motor_pid->goal_value = 0;
	motor_pid->error[0] = motor_pid->error[1] = 0;
}

float PID_LimitMax(float intput,float max)
{
	if(intput>max)   	  intput = max;
	else if(intput<-max)  intput = -max;
	return intput;
}

float PID_Calculate(MOTOR_PID *Motor_pid,float get,float set)
{
	Motor_pid->error[0] = set - get;
	
	Motor_pid->P_out = Motor_pid->speed_kp * Motor_pid->error[0];
	Motor_pid->I_out += Motor_pid->speed_ki * Motor_pid->error[0];
	Motor_pid->D_out = Motor_pid->speed_kd * (Motor_pid->error[0] - Motor_pid->error[1]);
	
	PID_LimitMax(Motor_pid->I_out,Motor_pid->MAX_Iout);
	
	Motor_pid->out = Motor_pid->P_out + Motor_pid->I_out + Motor_pid->D_out;
	PID_LimitMax(Motor_pid->out, Motor_pid->MAX_out);

	Motor_pid->error[1] = Motor_pid->error[0];
	return Motor_pid->out;
}
