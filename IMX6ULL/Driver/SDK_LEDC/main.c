#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "main.h"

int main(void)
{
    /* 1 使能GPIO1时钟*/
    CCM->CCGR0 |= CCGRx_VALUE;  /* 使能所有外设时钟 */
    CCM->CCGR1 |= CCGRx_VALUE;  /* 使能所有外设时钟 */
    CCM->CCGR2 |= CCGRx_VALUE;  /* 使能所有外设时钟 */
    CCM->CCGR3 |= CCGRx_VALUE;  /* 使能所有外设时钟 */
    CCM->CCGR4 |= CCGRx_VALUE;  /* 使能所有外设时钟 */
    CCM->CCGR5 |= CCGRx_VALUE;  /* 使能所有外设时钟 */
    CCM->CCGR6 |= CCGRx_VALUE;  /* 使能所有外设时钟 */

    /* 2 配置GPIO1_IO03引脚复用功能和属性 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);  /* 配置引脚复用为GPIO */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, GPIO1_IO03_PAD_VALUE);  /* 配置引脚属性 */

    /* 3 配置GPIO1_IO03为输出功能 */
    GPIO1->GDIR |= GPIO1_IO03_BIT;  /* bit3 对应GPIO1_IO03 */
    GPIO1->DR |= GPIO1_IO03_LOW;  /* 默认输出高电平，关闭LED */

    while (1);
    return 0;
}