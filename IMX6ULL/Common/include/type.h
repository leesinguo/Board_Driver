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

#endif /* __TYPE_H__ */