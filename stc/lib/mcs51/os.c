#include "os.h"

u8 TaskId = 0;
u8 NextTaskId = 0;

u8 TaskTicks[OS_TASKS];
u8 TaskStatus = 0xff;
u8 CriticalCount = 0;
u8 const BitMasks[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void TaskSchedule(void)
{
    ENTER_CRITICAL();
    for (NextTaskId = 0; NextTaskId < OS_TASKS; NextTaskId++)
    {
        if ((TaskStatus & (1 << NextTaskId)) != 0)
        {
            //TaskSwitch(NextTaskId)
            return;
        }
    }
    //TO-DO run idle task
    EXIT_CRITICAL();
}

void TaskReady(u8 taskId)
{
    ENTER_CRITICAL();
    TaskStatus |= 1 << taskId;
    EXIT_CRITICAL();
    //TaskSchedule();
}

void TaskSuspend(u8 taskId)
{
    ENTER_CRITICAL();
    TaskStatus &= ~(1 << taskId);
    EXIT_CRITICAL();
    //TaskSchedule();
}

void TaskSleep(u8 ticks)
{
    if (ticks == 0) return;
    TaskTicks[TaskId] = ticks;
    TaskSuspend(TaskId);
}

// void OSIntExit(void)
// {
//     u8 temp;

//     OS_ENTER_CRITICAL();
        
//         Os_Enter_Sum = 0;            
//         temp = OSTaskRuning;
//         for (OSNextTaskID = 0; OSNextTaskID < OS_MAX_TASKS; OSNextTaskID++)
//         {
//             if ((temp & 0x01) != 0)
//             {
//                 break;
//             }
//             temp = temp >> 1;
//         }
//         OSIntCtxSw();               
//     EXIT_CRITICAL();
// }


// void  OSTimeTick(void)
// {
//     uint8 i;

//     for (i = 0; i < OS_MAX_TASKS; i++)                 
//     {
//         if (OSWaitTick[i] != 0 )
//         {
//             OSWaitTick[i]--;
//             if (OSWaitTick[i] == 0)
//             {
//                 OSIntSendSignal(i);
//             }
//         }
//     }
// }


// void TaskIdle(void)
// {
//     while(1)
//     {
//         PCON = PCON | 0x01;                     /* CPU进入休眠状态 */
//     }
// }