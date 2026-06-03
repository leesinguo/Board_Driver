#ifndef __MAIN_H__
#define __MAIN_H__

/* 时钟使能寄存器地址 */
#define CCGR0       0x020C4068
#define CCGR1       0x020C406C
#define CCGR2       0x020C4070
#define CCGR3       0x020C4074
#define CCGR4       0x020C4078
#define CCGR5       0x020C407C
#define CCGR6       0x020C4080

/* 引脚复用配置寄存器地址 */
#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03    0x020E0068

/* 引脚属性配置寄存器地址 */
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03    0x020E02F4

/* GPIO1寄存器地址 */
#define GPIO1_GDIR  0x0209C004  /* GPIO1方向寄存器，1=输出，0=输入 */
#define GPIO1_DR    0x0209C000  /* GPIO1数据寄存器 */

/* 配置值 */
#define CCGRx_VALUE             0xffffffff      /* 使能所有外设时钟 */
#define GPIO1_IO03_MUX_VALUE    0x5             /* 配置引脚复用为GPIO */
#define GPIO1_IO03_PAD_VALUE    0x10B0          /* 配置引脚属性 */
#define GPIO1_IO03_BIT          0x8             /* bit3 对应GPIO1_IO03 */
#define GPIO1_IO03_LOW          0x0             /* 低电平点亮LED */
#define GPIO1_IO03_HIGH         0x8             /* 高电平关闭LED */

typedef unsigned int uint32_t;

#endif /* __MAIN_H__ */
