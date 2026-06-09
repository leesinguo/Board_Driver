#ifndef __KEY_H_
#define __KEY_H_

#include "type.h"

/* 配置值 */
#ifndef CCGRx_VALUE
#define CCGRx_VALUE                 0xffffffff      /* 使能所有外设时钟 */
#endif

/* API 函数声明 */
void key_init(void);
uint32_t key_getvalue(void);

#endif // !__KEY_H_
