#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "delay.h"
#include "type.h"
#include "main.h"

LOCAL void led_trigger(void)
{
    GPIO1->DR &= ~GPIO_HIGH(3);  /* 输出低电平，打开LED */
    delay(1000);                   /* 延时 */
    GPIO1->DR |= GPIO_HIGH(3);   /* 输出高电平，关闭LED */
}

int main(void)
{
    /* 使能时钟 */
    CCM->CCGR0 |= CCGRx_VALUE;
    CCM->CCGR1 |= CCGRx_VALUE;
    CCM->CCGR2 |= CCGRx_VALUE;
    CCM->CCGR3 |= CCGRx_VALUE;
    CCM->CCGR4 |= CCGRx_VALUE;
    CCM->CCGR5 |= CCGRx_VALUE;
    CCM->CCGR6 |= CCGRx_VALUE;

    /* 配置Key引脚 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, GPIO_PAD_VALUE_INPUT);

    /* 配置LED引脚 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);                  /* 配置引脚复用为GPIO */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, GPIO_PAD_VALUE_OUTPUT);  /* 配置引脚属性 */

    /* 配置BEEP引脚 */
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, GPIO_PAD_VALUE_OUTPUT);

    /* 配置GPIO1_IO03为输出功能 */
    GPIO1->GDIR |= GPIO_HIGH(3);  /* bit3 对应GPIO1_IO03 */

    /* 配置GPIO5_IO01为输出功能 */
    GPIO5->GDIR |= GPIO_HIGH(1);  /* bit1 对应GPIO5_IO01 */
    GPIO5->DR |= GPIO_HIGH(1);    /* 输出高电平，关闭BEEP */

    /* 配置GPIO1_IO18为输入 */
    GPIO1->GDIR &= ~GPIO_HIGH(18); /* bit18 对应GPIO1_IO18 */

    while(1) {
        led_trigger();  /* LED闪烁 */
        /* 读取按键状态，控制蜂鸣器 */
        if (!(GPIO1->DR & GPIO_HIGH(18))) {  /* Key按下 */
            GPIO5->DR &= ~GPIO_HIGH(1);       /* 输出低电平，打开BEEP */
        } else {                               /* Key松开 */
            GPIO5->DR |= GPIO_HIGH(1);        /* 输出高电平，关闭BEEP */
        }
        delay(20);  /* 延时，用于消抖 */
    }
    return 0;
}
