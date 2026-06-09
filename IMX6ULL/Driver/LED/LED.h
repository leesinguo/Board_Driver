#ifndef __LED_H_
#define __LED_H_

#include "type.h"

/* 配置值 */
#ifndef CCGRx_VALUE
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */
#endif

/* API 函数声明 */
void led_init(void);
void led_switch(int led, uint32_t status);

#endif // !__LED_H_
