#ifndef __BEEP_H_
#define __BEEP_H_

#include "type.h"

/* 配置值 */
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */

/* API 函数声明 */
void beep_init(void);
void beep_switch(uint32_t status);

#endif // !__BEEP_H_
