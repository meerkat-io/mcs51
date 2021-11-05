#include "os.h"

u8 task_id = 0;
u8 tasks_delay[OS_TASKS];
u8 tasks_status = 0xff;
u8 tasks_stack[OS_TASKS][TASK_STACK_SIZE];
u8 tasks_sp[OS_TASKS];
u8 task_idle_stack[16];

u8 const BIT_MASKS[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void task_switch(void)
{
    u8 id = 0;
    while (id < OS_TASKS)
    {
        // status 0:suspend, 1:ready
        if ((tasks_status & BIT_MASKS[id]) != 0)
        {
            task_id = id;
            //TaskSwitch()
            return;
        }
        id++;
    }
    //TO-DO run idle task
}

void task_idle(void)
{
    while (1)
    {
        idle_mode();
    }    
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
}