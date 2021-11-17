#ifndef CPU_H
#define CPU_H

#include "config.h"
#include "compiler.h"

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

#define FALSE 0
#define TRUE  1

#define GPIO_INPUT                  0
#define GPIO_INPUT_PULL_UP          1
#define GPIO_OUTPUT_PUSH_PULL       2
#define GPIO_OUTPUT_OPEN_DRAIN      3

#define	GPIO_MODE_0(port, pin)          P##port##M1 |= BIT_MASKS[pin], P##port##M0 &= ~BIT_MASKS[pin]
#define	GPIO_MODE_1(port, pin)          P##port##M1 &= ~BIT_MASKS[pin), P##port##M0 &= ~BIT_MASKS[pin]
#define	GPIO_MODE_2(port, pin)          P##port##M1 |= BIT_MASKS[pin], P##port##M0 |= BIT_MASKS[pin]
#define	GPIO_MODE_3(port, pin)          P##port##M1 &= ~BIT_MASKS[pin], P##port##M0 |= BIT_MASKS[pin]

#define CLOCK_DIVIDE_1()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_2()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define CLOCK_DIVIDE_4()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_8()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define CLOCK_DIVIDE_16()           CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_32()           CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define CLOCK_DIVIDE_64()           CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_128()          CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0

#define TIMER_0_1T()        AUXR |= BIT_MASK_7
#define TIMER_1_1T()        AUXR |= BIT_MASK_6
#define TIMER_2_1T()        AUXR |= BIT_MASK_2
#define TIMER_3_1T()        T4T3M |= BIT_MASK_1
#define TIMER_4_1T()        T4T3M |= BIT_MASK_5

#define START_TIMER_0()     TR0 = 1
#define START_TIMER_1()     TR1 = 1
#define START_TIMER_2()     T2R = 1
#define START_TIMER_3()     T3R = 1
#define START_TIMER_4()     T4R = 1
#define STOP_TIMER_0()      TR0 = 0
#define STOP_TIMER_1()      TR1 = 0
#define STOP_TIMER_2()      T2R = 0
#define STOP_TIMER_3()      T3R = 0
#define STOP_TIMER_4()      T4R = 0

#define LOAD_TIMER_0(time)        TL0 = time & 0xff, TH0 = time >> 8
#define LOAD_TIMER_1(time)        TL1 = time & 0xff, TH1 = time >> 8
#define LOAD_TIMER_2(time)        T2L = time & 0xff, T2H = time >> 8
#define LOAD_TIMER_3(time)        T3L = time & 0xff, T3H = time >> 8
#define LOAD_TIMER_4(time)        T4L = time & 0xff, T4H = time >> 8

#define __gpio_mode(mode, port, pin)              GPIO_MODE_##mode(port, pin)
#define gpio_mode(mode, port, pin)                __gpio_mode(mode, port, pin)
#define __clock_divide(freq)                      CLOCK_DIVIDE_##freq()
#define clock_divide(freq)                        __clock_divide(freq)
#define __timer_12x(timer)                        TIMER_##timer##_1T()
#define timer_12x(timer)                          __timer_12x(timer)
#define reset_timer()                             TMOD = 0x00
#define __load_timer(timer, time)                 LOAD_TIMER_##timer(time)
#define load_timer(timer, time)                   __load_timer(timer, time)
#define __start_timer(timer)                      START_TIMER_##timer()
#define start_timer(timer)                        __start_timer(timer)
#define __stop_timer(timer)                       STOP_TIMER_##timer()
#define stop_timer(timer)                         __stop_timer(timer)
#define __enable_timer_interrupt(timer, enable)   ET##timer = enable
#define enable_timer_interrupt(timer, enable)     __enable_timer_interrupt(timer, enable)

#define enter_critical()    EA = 0                /* disable interrupt */
#define exit_critical()     EA = 1                /* enable interrupt */

extern u8 const BIT_MASKS[];
#endif