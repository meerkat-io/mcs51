#ifndef OS_H
#define OS_H

#include "config.h"
#include "cpu.h"

#define i8 char
#define u8 unsigned char
#define i16 short
#define u16 unsigned short
#define i32 long
#define u32 unsigned long

#define BIT_MASK_0 0x01
#define BIT_MASK_1 0x02
#define BIT_MASK_2 0x04
#define BIT_MASK_3 0x08
#define BIT_MASK_4 0x10
#define BIT_MASK_5 0x20
#define BIT_MASK_6 0x40
#define BIT_MASK_7 0x80

extern u8 CriticalCount;
extern u8 const BitMasks[];

#endif