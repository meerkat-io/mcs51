#include "os.h"
#include "lint.h"

u8 task_id = 0;
u8 tasks_delay[OS_TASKS];
u8 tasks_status = 0xff; // status 0:suspend, 1:ready
u8 TASK_STACK_LOCATION tasks_stack[OS_TASKS][TASK_STACK_SIZE];
u8 tasks_sp[OS_TASKS];
u8 task_idle_stack[16];

u8 const BIT_MASKS[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void task_switch(void)
{
    u8 id = 0;
    while (id < OS_TASKS)
    {
        if ((tasks_status & BIT_MASKS[id]) != 0)
        {
            task_id = id;
            task_start(id);
            enter_critical();
            break;
        }
        id++;
    }
}

void task_idle(void)
{
    while (1)
    {
        task_switch();
    }    
}

void task_suspend()
{
    task_save();
    tasks_status &= ~BIT_MASKS[task_id];
    enter_idle_mode();
}     

void os_wait(u8 ticks)
{
    task_save();
    tasks_delay[task_id] = ticks;
    enter_idle_mode();
}

void os_start(void)
{
    enter_critical();

    // set timer
    clock_divide(OS_TIMER_DIVISION);
    #ifdef OS_TIMER_MODE_1T
    timer_12x(OS_TIMER);
    #endif
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
    enter_critical();

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

    exit_critical();
}