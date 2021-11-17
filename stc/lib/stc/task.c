#include "task.h"

u8 const BIT_MASKS[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

#if TASKS > 0
u8 __idata task_update = FALSE;
u8 __idata task_id = 0;
u8 __idata task_delay[TASKS];
u8 __idata task_status = 0xff; // status 0:suspend, 1:ready

void task_run(void)
{
    exit_critical();
    while (1)
    {  
        while (task_update)
        {
            enter_critical();
            task_update = FALSE;
            u8 i = 0;
            while (i < TASKS)
            {
                if (task_delay[i] != 0)
                {
                    task_delay[i]--;
                    if (task_delay[i] == 0)
                    {
                        task_ready(i);
                    }
                }
                if ((task_status & BIT_MASKS[i]) != 0)
                {
                    task_id = i;
                    tasks[i]();
                }
                i++;
            }
            exit_critical();
        }
    }
}

void task_start(void)
{
    // set timer
#if TASK_TIMER_MODE_1T > 0
    timer_12x(TASK_TIMER);
#endif
    load_timer(TASK_TIMER, TASK_TIMER_RELOAD);
    start_timer(TASK_TIMER);
    enable_timer_interrupt(TASK_TIMER, TRUE);

    u8 i = 0;
    while (i < TASKS)
    {
        task_delay[i] = 0;
        i++;
    }
}

void task_tick(void) __interrupt(TASK_TIMER_ISR)
{
    task_update = TRUE;
}
#endif