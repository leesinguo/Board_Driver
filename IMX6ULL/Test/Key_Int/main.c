#include "Beep.h"
#include "Key.h"
#include "LED.h"
#include "Clock.h"
#include "delay.h"
#include "gpio.h"
#include "Interrupt.h"
#include "MCIMX6Y2.h"

/* 中断处理函数 */
void gpio1_18_irq_handler(uint32_t gicciarr_num, void *param)
{
    static uint8_t state = 0;
    delay(10);
    if (gpio_pin_read(GPIO1, GPIOx_IO18) == 0) {
        state = !state;
        beep_switch(state);
    }
    /* 清除中断标志位 */
    clear_gpio_interrupt_flag(GPIO1, GPIOx_IO18);
}

int main(void)
{
    gpio_pin_config_t conf = {0};
    uint32_t i = 0;
    uint8_t led_state = 0;

    conf.trigger_type = FALLING_EDGE_TRIGGER;
    conf.irq_num = GPIO1_Combined_16_31_IRQn;

    imx_interrupt_init();    
    system_clock_init_696mhz();
    device_clock_enable();
    key_init();
    led_init();
    beep_init();
    gpio_interrupt_init(GPIO1, GPIOx_IO18, &conf);

    while(1){
        i++;
        if (i == 50) {
            i = 0;
            led_state = !led_state;
            led_switch(0, led_state);
        }
        delay(10);
    }
    return 0;
}
