#include "type.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "gpio.h"

/* 控制GPIO高低电平 */
void gpio_pin_write(GPIO_Type *const base, const uint32_t pin, const uint8_t value)
{
    if (value == GPIO_LOW) {
        base->DR &= ~GPIO_HIGH(pin);
    } else {
        base->DR |= GPIO_HIGH(pin);
    }
}

/* 获取GPIO pin值*/
uint8_t gpio_pin_read(const GPIO_Type *base, const uint32_t pin)
{
    uint32_t value;

    value = base->DR;
    value &= GPIO_HIGH(pin);

    return !!value;
}

/* GPIO初始化 */
void gpio_init(GPIO_Type *const base, const uint32_t pin, const gpio_pin_config_t *config)
{
    /* 0 -> input 1 -> output*/
    if (config->dir == KGPIO_INPUT) {
        base->GDIR &= ~GPIO_HIGH(pin);
    } else {
        base->GDIR |= GPIO_HIGH(pin);
        /* 设置默认输出电平 */
        gpio_pin_write(base, pin, config->output_logic);
    }
}