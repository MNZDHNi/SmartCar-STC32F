#include "u_distinguish.h" 
#include "u_adc.h"
#include "u_adc_process.h"

// flag
char trace_flag = STRAIGHT;

void distinguish_path(void)
{
    if( Left_Adc ==100 && Right_Adc>75)   //Left_Adc>95 && Left_Adc<=100
    {
        in_island_cnt++;         //计数一定值认为有环岛
        if(in_island_cnt>=2)
        {
            in_island_cnt=0;
            into_island_flag = 1;  //置位环岛标志
        }
    }


    if(into_island_flag==1)  IN_island_encoder += temp_right_pluse;  //累计编码值
    if(IN_island_encoder >= IN_ISLAND_ENCODER_MAX)     //路程够了，代表已经进入环岛
    {
        into_island_flag = 0;         //清空环岛标志位
        IN_island_encoder = 0;
    }
    if(into_island_flag==1 && out_island_flag==0 && Straight_Angle_flag==0)   //入环岛检测
    {
        //PID计算
        Round_PWM_L = PID_Calculate(&pid_motor_left,Left_motor.get_encoder_speed,IN_ROUND_SPEED_L);   
        Round_PWM_R = PID_Calculate(&pid_motor_right,Right_motor.get_encoder_speed,IN_ROUND_SPEED_R);  
        //给电机控制值	
        Motor_Left_Command(Round_PWM_L);
        Motor_Right_Command(Round_PWM_R);
    }
    if((Left_Adc<50&& Right_Adc<40 && Middle_Adc>25)|| \
		(Right_Adc<50&& Left_Adc<40 && Middle_Adc>25))
		Straight_Angle_flag = 1;                             //直角标志位
	if(Straight_Angle_flag==1)  Straight_Angle_encoder += (temp_left_pluse+temp_right_pluse)/2;  //累计编码
	if(Straight_Angle_encoder >= STRAIGHT_ANGLE_ENCODER)      //编码记到一定值认为已经转过直角
	{
		Straight_Angle_flag = 0;             //标志位清零
		Straight_Angle_encoder = 0;          //累计编码值清零
	}
}
