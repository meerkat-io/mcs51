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

#define GPIO_INPUT
#define GPIO_INPUT_PULL_UP
#define GPIO_OUTPUT_PUSH_PULL
#define GPIO_OUTPUT_OPEN_DRAIN

#define	GPIO_MODE_GPIO_INPUT(port, pin)                     P##port##M1 |= BIT_MASKS[pin], P##port##M0 &= ~BIT_MASKS[pin]
#define	GPIO_MODE_GPIO_INPUT_PULL_UP(port, pin)             P##port##M1 &= ~BIT_MASKS[pin), P##port##M0 &= ~BIT_MASKS[pin]
#define	GPIO_MODE_GPIO_OUTPUT_PUSH_PULL(port, pin)          P##port##M1 |= BIT_MASKS[pin], P##port##M0 |= BIT_MASKS[pin]
#define	GPIO_MODE_GPIO_OUTPUT_OPEN_DRAIN(port, pin)         P##port##M1 &= ~BIT_MASKS[pin], P##port##M0 |= BIT_MASKS[pin]

#define CLOCK_DIVIDE_1()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_2()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define CLOCK_DIVIDE_4()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_8()            CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define CLOCK_DIVIDE_16()           CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_32()           CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define CLOCK_DIVIDE_64()           CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define CLOCK_DIVIDE_128()          CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0

#define gpio_mode(mode, port, pin)      GPIO_MODE_##mode(port, pin)
#define clock_divide(freq)              CLOCK_DIVIDE_##freq()

#define enter_critical()    EA = 0                          /* disable interrupt */
#define exit_critical()     EA = 1                          /* enable interrupt */
#define idle()              PCON = PCON | 0x01              /* set cpu to idle */
#define enter_idle_mode()   SP = (u8)task_idle_stack + 1    /* enter cpu idle mode */

#define task_ready(id)      tasks_status |= BIT_MASKS[id]
#define task_suspend()      tasks_status &= ~BIT_MASKS[task_id], task_switch()
#define task_start(id)      SP = tasks_sp[id]
#define task_save()         tasks_sp[task_id] = SP
#define os_wait(ticks)      tasks_delay[task_id] = ticks, tasks_status &= ~BIT_MASKS[task_id], task_switch()

extern u8 task_id;
extern u8 tasks_delay[];
extern u8 tasks_status;

extern void (*const tasks[])(void);
extern u8 const BIT_MASKS[];

extern void task_switch(void);
extern void os_start(void);

// pulse, pwm

#endif