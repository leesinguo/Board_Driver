#include "Beep.h"
#include "Key.h"
#include "LED.h"
#include "Clock.h"
#include "delay.h"
#include "gpio.h"
#include "Interrupt.h"
#include "epit.h"
#include "MCIMX6Y2.h"

int main(void)
{
    uint8_t led_state = 0;

    imx_interrupt_init();    
    system_clock_init_528mhz();
    device_clock_enable();
    led_init();
    delay_init();

    while(1){
        led_state = !led_state;
        led_switch(LED1, led_state);
        delay_ms(500);
    }
    return 0;
}
