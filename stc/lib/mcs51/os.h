#ifndef OS_H
#define OS_H

#include "config.h"

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

#define GPIO_LOW  0
#define GPIO_HIGH 1

#define	gpio_input(port, pin)                   P##port##M1 |= BIT_MASKS[pin], P##port##M0 &= ~BIT_MASKS[pin]
#define	gpio_input_pull_up(port, pin)           P##port##M1 &= ~BIT_MASKS[pin), P##port##M0 &= ~BIT_MASKS[pin]
#define	gpio_output_push_pull(port, pin)        P##port##M1 |= BIT_MASKS[pin], P##port##M0 |= BIT_MASKS[pin]
#define	gpio_output_open_drain(port, pin)       P##port##M1 &= ~BIT_MASKS[pin], P##port##M0 |= BIT_MASKS[pin]	

#define timer_clock_division_1()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define timer_clock_division_2()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define timer_clock_division_4()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define timer_clock_division_8()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define timer_clock_division_16()   CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define timer_clock_division_32()   CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define timer_clock_division_64()   CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define timer_clock_division_128()  CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0

#define enter_critical()    EA = 0                      /* disable interrupt */
#define exit_critical()     EA = 1                      /* enable interrupt */
#define idle_mode()         PCON = PCON | 0x01          /* set cpu to idle */

#define task_ready(id)      tasks_status |= BIT_MASKS[id]
#define task_suspend()      tasks_status &= ~BIT_MASKS[task_id], task_switch()
#define task_wait(ticks)    tasks_delay[task_id] = ticks, tasks_status &= ~BIT_MASKS[task_id], task_switch()

extern u8 const BIT_MASKS[];

void task_switch(void);

// pulse, pwm

#endif