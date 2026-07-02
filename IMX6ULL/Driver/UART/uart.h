#ifndef __UART_H_
#define __UART_H_

#include "type.h"

#define TRANSMITTER_COMPLETE    1
#define RECEIVE_READY           1

/* 日志等级定义 */
#define DLOG_DEBUG              0
#define DLOG_INFO               1
#define DLOG_ERROR              2
typedef struct {
    uint32_t baud_rate;
    uint8_t stop_bit;
    uint8_t parity_check_bit;
    uint8_t data_bit;
}uart_conf_t;

extern void uart1_init_115200(void);
extern void putc(uint8_t data);
extern uint8_t getc(void);
extern void puts(uint8_t *str);
extern void debug_log(uint8_t level, const int8_t *format, ...);

/* 全局调试日志等级变量，可在任意位置修改以过滤输出 */
extern uint8_t g_debug_log_level;

#endif // !__UART_H_