#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "gpio.h"
#include "LED.h"

void led_init(void)
{
    gpio_pin_config_t gpio_config = {0};

    /* 配置LED引脚（GPIO1_IO03） */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, GPIO_PAD_VALUE_OUTPUT);

    /* LED: GPIO1_IO03 设为输出，初始高电平（LED灭） */
    gpio_config.dir = KGPIO_OUTPUT;
    gpio_config.output_logic = HIGH_LEVEL;
    gpio_init(GPIO1, GPIOx_IO03, &gpio_config);
}

void led_switch(int led, uint32_t status)
{
    switch (led) {
    case 0:
        switch (status) {
        case DEVICE_ENABLE:
            gpio_pin_write(GPIO1, GPIOx_IO03, LOW_LEVEL);   /* 打开LED0 */
            break;
        case DEVICE_DISABLE:
            gpio_pin_write(GPIO1, GPIOx_IO03, HIGH_LEVEL);  /* 关闭LED0 */
            break;
        default:
            break;
        }
        break;
    }
}
