#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "main.h"

int main(void)
{
    uint32_t value;
    /* 使能时钟 */
    CCM->CCGR0 |= CCGRx_VALUE;
    CCM->CCGR1 |= CCGRx_VALUE;
    CCM->CCGR2 |= CCGRx_VALUE;
    CCM->CCGR3 |= CCGRx_VALUE;
    CCM->CCGR4 |= CCGRx_VALUE;
    CCM->CCGR5 |= CCGRx_VALUE;
    CCM->CCGR6 |= CCGRx_VALUE;

    /* 配置引脚 */
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, GPIO_PAD_VALUE);

    GPIO5->GDIR |= GPIO_HIGH(1);  /* bit5 对应GPIO1_IO05 */

    /* 输出低电平 */
    value = GPIO5->DR;
    value &= ~GPIO_HIGH(1); 
    GPIO5->DR = GPIO_LOW;
    while(1);
    return 0;
}