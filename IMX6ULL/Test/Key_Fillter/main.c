#include "Beep.h"
#include "Key.h"
#include "LED.h"
#include "Clock.h"
#include "delay.h"
#include "gpio.h"
#include "Interrupt.h"
#include "epit.h"
#include "MCIMX6Y2.h"

/* 定时器中断处理函数 */
void epit1_irq_handler(uint32_t gicciarr_num, void *param)
{
    static uint8_t beep_state = DEVICE_DISABLE;
    if (GET_REG_BIT(((EPIT_Type*)param)->SR, BIT0) == EPIT_COMPARE_EVENT_OCCURRED) {
        /* 关闭定时器 */
        epit_disable((EPIT_Type*)param);
        /* 按键判断 */
        if (gpio_pin_read(GPIO1, GPIOx_IO18) == 0) {
            beep_state = !beep_state;
            beep_switch(beep_state);
        }
    }
    /* 清除中断标志位 */
    clear_epit_interrupt_flag((EPIT_Type*)param);
}

/* 中断处理函数 */
void gpio1_18_irq_handler(uint32_t gicciarr_num, void *param)
{
    /* 启动定时器 */
    /* 配置定时器 */
    epit_config_t conf;
    conf.clk_frac = 65;
    conf.cmp_value = 0;
    conf.load_value = 100000;       /* 10毫秒 */
    conf.count_value = conf.load_value;
    epit_init(EPIT1, &conf);
    clear_gpio_interrupt_flag(((gpio_interrupt_params_t*)param)->ptr,
        ((gpio_interrupt_params_t*)param)->pin_num);
}

int main(void)
{
    gpio_pin_config_t conf = {0};
    uint32_t i = 0;
    uint8_t led_state = 0;

    conf.trigger_type = FALLING_EDGE_TRIGGER;
    conf.irq_num = GPIO1_Combined_16_31_IRQn;

    imx_interrupt_init();    
    system_clock_init_528mhz();
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
            led_switch(LED1, led_state);
        }
        delay_ms(10);
    }
    return 0;
}
