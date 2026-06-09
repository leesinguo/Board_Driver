#include "Beep.h"
#include "Key.h"
#include "LED.h"
#include "delay.h"

int main(void)
{
    uint8_t beep_state = 0;
    uint8_t led_state = 0;
    int32_t i = 0;

    key_init();
    led_init();
    beep_init();

    while (1) {
        uint32_t key_value;
        key_value = key_getvalue();  /* 读按键状态 */
        if (key_value) {
            switch (key_value) {
            case 1:
                beep_state = !beep_state;
                beep_switch(beep_state);
                break;
            }
        }

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
