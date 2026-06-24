#ifndef __LED_H_
#define __LED_H_

#include "type.h"

/* 配置值 */
#ifndef CCGRx_VALUE
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */
#endif
typedef enum {
    LED1 = 1,
}Ledn_t;

/* API 函数声明 */
extern void led_init(void);
extern void led_switch(Ledn_t led, uint32_t status);

#endif // !__LED_H_
