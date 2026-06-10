#ifndef __CLOCK_H_
#define __CLOCK_H_

#include "type.h"

/* 配置值 */
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */
void device_clock_enable(void);
void system_clock_init_528mhz(void);
void system_clock_init_696mhz(void);

#endif // !__CLOCK_H_