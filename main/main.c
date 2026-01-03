#include "headfile.h"
#include "u_config.h"

volatile long int tcnt = 0;

void main()
{
	//value init
	float x = 0;
	int y = 0, z = 0, i = 0, j = 0;

	//init function
	clock_init(SYSTEM_CLOCK_52M);	// 初始化系统频率
	board_init();					// 初始化寄存器

	lcd_init();					// 初始化液晶显示屏

	U_ADC_Init();
	U_PWM_Init();
	u_encoder_init();

	// 测试encoder和pwm
	pit_timer_ms(TIM_1, 10);	// 初始化定时器1，10ms中断一次
	// U_PWM_SetDuty(1000, 1000);


	while(1)
	{
		// 测试adc
		U_ADC_Read();

		lcd_showuint16(0, 0, adc_value[0][0]);
		lcd_showuint16(0, 1, adc_value[0][1]);
		lcd_showuint16(0, 2, adc_value[0][2]);
		lcd_showuint16(0, 3, adc_value[0][3]);
		
		x = u_adc_process(adc_value);

		lcd_showfloat(0, 4, x, 8, 2);



		// // 测试encoder和pwm
		// EA = 1;

		// u_encoder_open();
		// y = (unsigned int)left_count;
		// z = (unsigned int)right_count;
		// lcd_showuint16(0, 5, y);
		// lcd_showuint16(0, 6, z);

		// i = left_count / tcnt / 100;
		// j = right_count / tcnt / 100;

		// lcd_showuint16(0, 7, i);
		// lcd_showuint16(0, 8, j);

	}
}


void timer1_interrupt(void) interrupt 3
{
	tcnt++;
}
