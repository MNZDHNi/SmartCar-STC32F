#include "headfile.h"
#include "u_config.h"

char x = 114;

void main()
{
	//init function
	clock_init(SYSTEM_CLOCK_52M);	// 初始化系统频率
	board_init();					// 初始化寄存器

	lcd_init();					// 初始化液晶显示屏
	lcd_showint8(0,0,x);		// 显示有符号8位整数
	lcd_showint8(0,1,x);
	lcd_showint8(0,2,x);

	U_PWM_Init();
	U_PWM_SetDuty(1000, 5000);


	while(1)
	{
		
	}
}
