#ifndef __TYPE_H__
#define __TYPE_H__

typedef int                 int32_t;
typedef short               int16_t;
typedef char                int8_t;
typedef long long           int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef	  signed char  	 	   s8;		
typedef	  signed short 	  int  s16;
typedef	  signed int 		   s32;
typedef	  signed long long int s64;
typedef	unsigned char 		   u8;
typedef	unsigned short int     u16;
typedef	unsigned int 		   u32;
typedef	unsigned long long int u64;

#define     LOCAL      static

#define     __I     volatile 
#define     __O     volatile 
#define     __IO    volatile

#define LOW_LEVEL                   0x0
#define HIGH_LEVEL                  0x1
#define DEVICE_ENABLE               0x1
#define DEVICE_DISABLE              0x0   

/* BIT0 ~ BIT31 位号定义 */
#define BIT0         0
#define BIT1         1
#define BIT2         2
#define BIT3         3
#define BIT4         4
#define BIT5         5
#define BIT6         6
#define BIT7         7
#define BIT8         8
#define BIT9         9
#define BIT10        10
#define BIT11        11
#define BIT12        12
#define BIT13        13
#define BIT14        14
#define BIT15        15
#define BIT16        16
#define BIT17        17
#define BIT18        18
#define BIT19        19
#define BIT20        20
#define BIT21        21
#define BIT22        22
#define BIT23        23
#define BIT24        24
#define BIT25        25
#define BIT26        26
#define BIT27        27
#define BIT28        28
#define BIT29        29
#define BIT30        30
#define BIT31        31

/* 读取寄存器第 n 位的值（0 或 1） */
#define GET_REG_BIT(reg, n)          (((reg) >> (n)) & 1U)

/* 读取寄存器 [msb:lsb] 位域的值（右对齐） */
#define GET_REG_FIELD(reg, msb, lsb) (((reg) >> (lsb)) & ((1UL << ((msb) - (lsb) + 1)) - 1))

/* 设置寄存器第 n 位为 1 */
#define SET_REG_BIT(reg, n)          ((void)((reg) |= (1UL << (n))))

/* 清除寄存器第 n 位为 0 */
#define CLR_REG_BIT(reg, n)          ((void)((reg) &= ~(1UL << (n))))

/* 设置寄存器 [msb:lsb] 位域的值 */
#define SET_REG_FIELD(reg, msb, lsb, value) \
    ((void)((reg) = ((reg) & ~((1UL << ((msb) - (lsb) + 1)) - 1) << (lsb)) | \
                    (((uint32_t)(value) & ((1UL << ((msb) - (lsb) + 1)) - 1)) << (lsb))))

#endif /* __TYPE_H__ */