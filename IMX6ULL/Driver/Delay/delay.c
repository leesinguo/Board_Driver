
#include "type.h"
#include "delay.h"

/*
 * @description	: 短时间延时函数
 * @param - n	: 要延时循环次数(空操作循环次数，模式延时)
 * @return 		: 无
 */
void delay_short(volatile uint32_t conut)
{
	while(conut--){}
}

/*
 * @description	: 延时函数,在396Mhz的主频下
 * 			  	  延时时间大约为1ms
 * @param - n	: 要延时的ms数
 * @return 		: 无
 */
void delay(uint32_t count)
{
	while(count--)
	{
		delay_short(0x7ff);
	}
}
