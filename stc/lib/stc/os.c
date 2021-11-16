#include "os.h"

u8 __idata tick = 0;
u8 __idata task_id = 0;
u8 __idata task_idle_stack[16];
u8 __idata tasks_delay[OS_TASKS];
u8 __idata tasks_status = 0xff; // status 0:suspend, 1:ready
u8 __idata tasks_stack[OS_TASKS][TASK_STACK_SIZE];
u8 __idata tasks_sp[OS_TASKS];

u8 const BIT_MASKS[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void task_idle(void)
{
    while (1)
    {
        if (tick > 0)
        {
            enter_critical();
            u8 i = 0;
            while (i < OS_TASKS)
            {
                if ((tasks_status & BIT_MASKS[i]) != 0)
                {
                    task_resume(i);
                    return;
                }
                i++;
            }
            exit_critical();
        }
    }
}

void task_suspend()
{
    save_stack();
    tasks_status &= ~BIT_MASKS[task_id];
    enter_idle_mode();
}

void task_sleep(u8 ticks)
{
    save_stack();
    tasks_status &= ~BIT_MASKS[task_id];
    tasks_delay[task_id] = ticks;
    enter_idle_mode();
}

void os_start(void)
{
    enter_critical();
    // set timer
    clock_divide(TIMER_DIVISION);
#if OS_TIMER_MODE_1T > 0
    timer_12x(OS_TIMER);
#endif
    reset_timer();
    load_timer(OS_TIMER, OS_TIMER_RELOAD);
    start_timer(OS_TIMER);
    enable_timer_interrupt(OS_TIMER, TRUE);
    // init task
    task_idle_stack[0] = (u16)task_idle & 0xff;
    task_idle_stack[1] = (u16)task_idle >> 8;
    u8 i = 0;
    while (i < OS_TASKS)
    {
        tasks_delay[i] = 0;
        tasks_sp[i] = (u8)tasks_stack[i] + 1;
        tasks_stack[i][0] = (u16)tasks[i] & 0xff;
        tasks_stack[i][1] = (u16)tasks[i] >> 8;
        i++;
    }
    // start first task
    task_start(0);
}

void os_tick(void) __interrupt(OS_TIMER_ISR)
{
    u8 i = 0;
    while (i < OS_TASKS)
    {
        if (tasks_delay[i] != 0)
        {
            tasks_delay[i]--;
            if (tasks_delay[i] == 0)
            {
                task_ready(i);
            }
        }
        i++;
    }
    tick++;
}