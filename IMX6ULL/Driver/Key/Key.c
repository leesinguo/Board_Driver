#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "delay.h"
#include "type.h"
#include "gpio.h"
#include "Key.h"

void key_init(void)
{
    gpio_pin_config_t gpio_config = {0};

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

    /* KEY: GPIO1_IO18 设为输入 */
    gpio_config.dir = KGPIO_INPUT;
    gpio_init(GPIO1, GPIOx_IO18, &gpio_config);
}

uint32_t key_getvalue(void)
{
    uint32_t ret = 0;
    static unsigned char release = 1; /* 按键松开 */

    if ((release == 1) && (gpio_pin_read(GPIO1, GPIOx_IO18) == 0)) {
        delay(10);              /* 延时消抖 */
        release = 0;            /* 标记按键按下 */
        if (gpio_pin_read(GPIO1, GPIOx_IO18) == 0)
            ret = 1;
    } else if (gpio_pin_read(GPIO1, GPIOx_IO18) == 1) {
        ret = 0;
        release = 1;            /* 标记按键释放 */
    }

    return ret;
}
