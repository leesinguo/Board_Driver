#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "delay.h"
#include "type.h"
#include "main.h"

LOCAL void led_trigger(void)
{
    GPIO1->DR &= ~(1 << 3);     /* LED LOW */
    delay(1000);                 /* 延时 1000ms */
    GPIO1->DR |= (1 << 3);      /* LED HIGH */
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

    /* 配置Key引脚（GPIO1_IO18） */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, GPIO_PAD_VALUE_INPUT);

    /* 配置LED引脚（GPIO1_IO03） */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, GPIO_PAD_VALUE_OUTPUT);

    /* 配置BEEP引脚（GPIO5_IO01） */
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, GPIO_PAD_VALUE_OUTPUT);

    /* ---- 直接寄存器操作（不使用 gpio API）---- */

    /* LED: GPIO1_IO03 设为输出，初始高电平（LED灭） */
    GPIO1->GDIR |= (1 << 3);
    GPIO1->DR   |= (1 << 3);

    /* BEEP: GPIO5_IO01 设为输出，初始高电平（蜂鸣器关） */
    GPIO5->GDIR |= (1 << 1);
    GPIO5->DR   |= (1 << 1);

    /* KEY: GPIO1_IO18 设为输入 */
    GPIO1->GDIR &= ~(1 << 18);

    while(1) {
        uint8_t key_value;

        key_value = !!(GPIO1->DR & (1 << 18));  /* 读按键状态 */
        led_trigger();                            /* LED闪烁 */
        /* 控制蜂鸣器 */
        if (!key_value) {           /* Key按下（低电平） */
            GPIO5->DR &= ~(1 << 1); /* 输出低电平，打开BEEP */
        } else {                    /* Key松开（高电平） */
            GPIO5->DR |= (1 << 1);  /* 输出高电平，关闭BEEP */
        }
        delay(20);                  /* 延时消抖 */
    }
    return 0;
}
