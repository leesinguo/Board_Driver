
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "type.h"
#include "gpio.h"
#include "uart.h"

/* 全局调试日志等级，在 uart1_init_115200 中显式初始化 */
uint8_t g_debug_log_level;

/* UART IO初始化 */
LOCAL void uart1_io_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, GPIO_PAD_VALUE_OUTPUT);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, GPIO_PAD_VALUE_INPUT);
}

LOCAL void close_uart(UART_Type *ptr)
{
    CLR_REG_BIT(ptr->UCR1, BIT0);
}

LOCAL void open_uart(UART_Type *ptr)
{
    SET_REG_BIT(ptr->UCR1, BIT0);
}

LOCAL void software_reset_uart(UART_Type *ptr)
{
    CLR_REG_BIT(ptr->UCR2, BIT0);
    while(GET_REG_BIT(ptr->UTS, BIT0) != 0);
}

void uart1_init_115200(void)
{
    /* 初始化日志等级 */
    g_debug_log_level = DLOG_DEBUG;

    /* 初始化UART1的IO */
    uart1_io_init();
    
    /* close uart */
    close_uart(UART1);

    /* software reset uart */
    software_reset_uart(UART1);

    /* 配置UART1 */
    CLR_REG_BIT(UART1->UCR1, BIT14);
    SET_REG_BIT(UART1->UCR2, BIT1);
    SET_REG_BIT(UART1->UCR2, BIT2);

    /* 8 bit data */
    SET_REG_BIT(UART1->UCR2, BIT5);
    
    /* 1 bit stop*/
    CLR_REG_BIT(UART1->UCR2, BIT6);

    /* disable parity check*/
    CLR_REG_BIT(UART1->UCR2, BIT8);
    
    /* ignore rts pin */
    SET_REG_BIT(UART1->UCR2, BIT14);
    
    SET_REG_BIT(UART1->UCR3, BIT2);

    /* 设置波特率115200 */
    /* 注意为了正确更新波特率，必须先更新 UBIR 寄存器，然后再更新 UBMR 寄存器*/
    SET_REG_FIELD(UART1->UFCR, BIT9, BIT7, 0x5);
    SET_REG_FIELD(UART1->UBIR, BIT15, BIT0, 71);
    SET_REG_FIELD(UART1->UBMR, BIT15, BIT0, 3124);

    /* open uart */
    open_uart(UART1);
}

/* 发送1字节数据 */
void putc(uint8_t data)
{
    /* 等待前一个数据发送完成 */
    while(GET_REG_BIT(UART1->USR2, BIT3) != TRANSMITTER_COMPLETE);
    SET_REG_FIELD(UART1->UTXD, BIT7, BIT0, data);
}

/* 接受数据 */
uint8_t getc(void)
{
    /* 等待数据 */
    while(GET_REG_BIT(UART1->USR2, BIT0) != RECEIVE_READY);
    return GET_REG_FIELD(UART1->URXD, BIT7, BIT0);
}

/* 发送多字节数据 */
void puts(uint8_t *str)
{
    if (str == NULL) {
        putc('E');
        putc('R');
        putc('R');
        putc('O');
        putc('R');
        putc('\r');
        putc('\n');
        return;
    }
    uint8_t *ptr = str;
    while(*ptr != '\0') {
        putc(*ptr);
        ptr++;
    }
}

/* 输出日志等级前缀 */
LOCAL void debug_log_prefix(int8_t level)
{
    switch (level) {
    case DLOG_DEBUG:
        puts((uint8_t *)"[DEBUG] ");
        break;
    case DLOG_INFO:
        puts((uint8_t *)"[INFO]  ");
        break;
    case DLOG_ERROR:
        puts((uint8_t *)"[ERROR] ");
        break;
    default:
        break;
    }
}

/* 调试日志输出，支持分级打印 */
void debug_log(uint8_t level, const int8_t *format, ...)
{
    __builtin_va_list args;
    uint8_t buf[12];
    int32_t i;

    /* 等级过滤：低于全局等级则不输出 */
    if (level < g_debug_log_level) {
        return;
    }

    if (format == NULL) {
        return;
    }

    /* 输出等级前缀 */
    debug_log_prefix(level);

    __builtin_va_start(args, format);

    while (*format != '\0') {
        if (*format != '%') {
            putc((uint8_t)*format);
            format++;
            continue;
        }

        format++; /* 跳过'%' */

        switch (*format) {
        case 'd':
        case 'i': {
            int32_t d = __builtin_va_arg(args, int32_t);
            if (d < 0) {
                putc((uint8_t)'-');
                d = -d;
            }
            i = 0;
            if (d == 0) {
                putc((uint8_t)'0');
            } else {
                while (d > 0) {
                    buf[i++] = (uint8_t)('0' + (d % 10));
                    d /= 10;
                }
                while (i > 0) {
                    putc((uint8_t)buf[--i]);
                }
            }
            break;
        }
        case 'u': {
            uint32_t u = __builtin_va_arg(args, uint32_t);
            i = 0;
            if (u == 0) {
                putc((uint8_t)'0');
            } else {
                while (u > 0) {
                    buf[i++] = (uint8_t)('0' + (u % 10));
                    u /= 10;
                }
                while (i > 0) {
                    putc((uint8_t)buf[--i]);
                }
            }
            break;
        }
        case 'x':
        case 'X': {
            uint32_t x = __builtin_va_arg(args, uint32_t);
            i = 0;
            if (x == 0) {
                putc((uint8_t)'0');
            } else {
                while (x > 0) {
                    int32_t digit = x % 16;
                    buf[i++] = (uint8_t)((digit < 10) ? ('0' + digit) : ('a' + digit - 10));
                    x /= 16;
                }
                while (i > 0) {
                    putc((uint8_t)buf[--i]);
                }
            }
            break;
        }
        case 'c': {
            int8_t c = (int8_t)__builtin_va_arg(args, int32_t);
            putc((uint8_t)c);
            break;
        }
        case 's': {
            int8_t *s = __builtin_va_arg(args, int8_t *);
            if (s == NULL) {
                s = (int8_t *)"(null)";
            }
            while (*s != '\0') {
                putc((uint8_t)*s);
                s++;
            }
            break;
        }
        case 'p': {
            void *p = __builtin_va_arg(args, void *);
            uint32_t addr = (uint32_t)p;
            putc((uint8_t)'0');
            putc((uint8_t)'x');
            i = 0;
            if (addr == 0) {
                putc((uint8_t)'0');
            } else {
                while (addr > 0) {
                    int32_t digit = addr % 16;
                    buf[i++] = (uint8_t)((digit < 10) ? ('0' + digit) : ('a' + digit - 10));
                    addr /= 16;
                }
                while (i > 0) {
                    putc((uint8_t)buf[--i]);
                }
            }
            break;
        }
        case '%': {
            putc((uint8_t)'%');
            break;
        }
        case '\0': {
            __builtin_va_end(args);
            return;
        }
        default: {
            putc((uint8_t)'%');
            putc((uint8_t)*format);
            break;
        }
        }
        format++;
    }

    /* 默认换行（\r\n） */
    putc((uint8_t)'\r');
    putc((uint8_t)'\n');

    __builtin_va_end(args);

}