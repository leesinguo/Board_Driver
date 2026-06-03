# Board_Driver
裸机驱动

## IMX6ULL

### 编译方法实例
1. 将.s、.c文件编译为.o
arm-linux-gnueabihf-gcc -g -c led.s -o led.o
2. 将.o文件链接elf文件
arm-linux-gnueabihf-ld -Ttext 0X87800000 led.o -o led.elf
3. 将.elf文件转为bin文件
arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
4. 反汇编(.elf -> .dis)
arm-linux-gnueabihf-objdump -D led.elf > led.dis

### LEDS
1. LED驱动汇编语言

### LEDC
1. LED驱动C语言
