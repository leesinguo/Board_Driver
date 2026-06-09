#include "type.h"
#include "imx6u.h"
#include "main.h"

int main(void)
{
    /* 使能所有外设时钟 */
    CCM->CCGR0 = CCGRx_VALUE;
    CCM->CCGR1 = CCGRx_VALUE;
    CCM->CCGR2 = CCGRx_VALUE;
    CCM->CCGR3 = CCGRx_VALUE;
    CCM->CCGR4 = CCGRx_VALUE;
    CCM->CCGR5 = CCGRx_VALUE;
    CCM->CCGR6 = CCGRx_VALUE;

    /* 配置GPIO1_IO03引脚复用 */
    IOMUX_SW_MUX->GPIO1_IO03 = GPIO1_IO03_MUX_VALUE;

    /* 配置GPIO1_IO03引脚属性 */
    IOMUX_SW_PAD->GPIO1_IO03 = GPIO1_IO03_PAD_VALUE;

    /* 配置GPIO1_IO03为输出模式 */
    GPIO1->GDIR |= GPIO1_IO03_BIT;

    /* 点亮LED */
    GPIO1->DR = GPIO1_IO03_LOW;

    /* 进入死循环 */
    while (1);

    return 0;
}
