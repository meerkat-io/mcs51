#ifndef TASK_H
#define TASK_H

#include "cpu.h"

#if TASKS > 0
#define task_ready(id)      task_status |= BIT_MASKS[id]
#define task_suspend()      task_status &= ~BIT_MASKS[task_id], task_delay[task_id] = 0
#define task_sleep(ticks)   task_status &= ~BIT_MASKS[task_id], task_delay[task_id] = ticks

extern __idata u8 task_id;
extern __idata u8 task_delay[];
extern __idata u8 task_status;
extern void (*const tasks[])(void);

extern void task_start(void);
extern void task_run(void);
extern void task_tick(void) __interrupt(TASK_TIMER_ISR);
#endif

#endif