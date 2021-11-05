#ifndef CONFIG_H
#define CONFIG_H

#include "stc15.h"                             /* the mcu to use */

#define OSC                6000000L               /* main osc frequency: 5529600L 11059200L 22118400L 6000000L 12000000L 24000000L*/

#define OS_TIMER           0                      /* os timer, default : use timer 0 */
#define OS_TIMER_ISR       1                      /* rtos timer interrupt (for timer 0) */ 
#define OS_TIMER_DIVISION  1                      /* timer frequency division */
#define OS_TIMER_MODE_1T   0                      /* use 1T timer mode: 1 yes, 0 no */
#define OS_TICK_FREQUENCY  100                    /* ticker frequency Hz */
#if OS_TIMER_MODE_1T > 0
#define OS_TIMER_RELOAD   (65535 - OSC/OS_TIMER_DIVISION/OS_TICK_FREQUENCY)
#else
#define OS_TIMER_RELOAD   (65535 - OSC/12/OS_TIMER_DIVISION/OS_TICK_FREQUENCY)
#endif

#define OS_TASKS                2                      /* task count, max 8 custom tasks */
#define TASK_STACK_LOCATION     __data                 /* task stack location : data, idata, xdata */
#define TASK_STACK_SIZE         8                      /* stack size pro task, 2 reserved for PC */

#endif