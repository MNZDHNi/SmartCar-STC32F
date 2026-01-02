#include "headfile.h"
#include "u_config.h"

char x = 114;

void main()
{
	//init function
	clock_init(SYSTEM_CLOCK_52M);	// 初始化系统频率
	board_init();					// 初始化寄存器

	while(1)
	{
		
	}
}
