#ifndef __MAIN_H_
#define __MAIN_H_

/* 配置值 */
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */
#define GPIO1_IO03_PAD_VALUE    0x10B0          /* 配置引脚属性 */
#define GPIO1_IO03_BIT          0x8             /* bit3 对应GPIO1_IO03 */
#define GPIO1_IO03_LOW          0x0             /* 低电平点亮LED */
#define GPIO1_IO03_HIGH         0x8             /* 高电平关闭LED */

#endif // !__MAIN_H_