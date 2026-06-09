#include "main.h"

static void write_reg(uint32_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
}

static uint32_t read_reg(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

int main(void)
{
    uint32_t value;

    /* 使能所有外设时钟 */
    write_reg(CCGR0, CCGRx_VALUE);
    write_reg(CCGR1, CCGRx_VALUE);
    write_reg(CCGR2, CCGRx_VALUE);
    write_reg(CCGR3, CCGRx_VALUE);
    write_reg(CCGR4, CCGRx_VALUE);
    write_reg(CCGR5, CCGRx_VALUE);
    write_reg(CCGR6, CCGRx_VALUE);

    /* 配置GPIO1_IO03引脚复用 */
    write_reg(IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03, GPIO1_IO03_MUX_VALUE);

    /* 配置GPIO1_IO03引脚属性 */
    write_reg(IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03, GPIO1_IO03_PAD_VALUE);

    /* 配置GPIO1_IO03为输出模式 */
    value = read_reg(GPIO1_GDIR);
    value |= GPIO1_IO03_BIT;
    write_reg(GPIO1_GDIR, value);

    /* 点亮LED */
    write_reg(GPIO1_DR, GPIO1_IO03_LOW);
    read_reg(GPIO1_DR);

    /* 进入死循环 */
    while (1);

    return 0;
}
