#ifndef __MAIN_H_
#define __MAIN_H_

/* 配置值 */
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */
#define GPIO_PAD_VALUE          0x10B0          /* 配置引脚属性 */
#define GPIO_LOW                0x0             
#define GPIO_HIGH(x)            (1<<x)   /* 输出高电平的值 */                       

#endif // !__MAIN_H_