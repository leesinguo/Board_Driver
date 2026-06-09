#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "gpio.h"
#include "Beep.h"

void beep_init(void)
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

    /* 配置引脚复用为 GPIO */
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);

    /* 配置引脚电气属性 */
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, GPIO_PAD_VALUE_OUTPUT);

    /* 设置 GPIO 方向为输出 */
    gpio_config.dir = KGPIO_OUTPUT;
    gpio_config.output_logic = HIGH_LEVEL;
    gpio_init(GPIO5, GPIOx_IO01, &gpio_config);
}

void beep_switch(uint32_t status)
{
    switch (status) {
    case DEVICE_ENABLE:
        gpio_pin_write(GPIO5, GPIOx_IO01, LOW_LEVEL);   /* 打开蜂鸣器 */
        break;
    case DEVICE_DISABLE:
        gpio_pin_write(GPIO5, GPIOx_IO01, HIGH_LEVEL);  /* 关闭蜂鸣器 */
    default:
        break;
    }
}
