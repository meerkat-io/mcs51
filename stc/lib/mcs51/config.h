#ifndef CONFIG_H
#define CONFIG_H

#include "stc15.h"                             /* the mcu to use */

#define OSC                6000000L               /* main osc frequency: 5529600L 11059200L 22118400L 6000000L 12000000L 24000000L*/

#define OS_TIMER_ISR       1                      /* rtos timer interrupt (for timer 0) */ 
#define OS_TIMER_DIVISION  1                      /* timer frequency division */
#define OS_TIMER_MODE_1T   0                      /* use 1T timer mode: 1 yes, 0 no */
#define OS_TICK_FREQUENCY  100                    /* ticker frequency Hz */
#if OS_TIMER_MODE_1T > 0
#define OS_TICK_INTERVAL   (65535 - OSC/OS_TIMER_DIVISION/OS_TICK_FREQUENCY)
#else
#define OS_TICK_INTERVAL   (65535 - OSC/12/OS_TIMER_DIVISION/OS_TICK_FREQUENCY)
#endif

#define OS_TASKS           2                      /* task count */

//SBIT(TIMER_MODE_BIT, _AUXR, BIT_MASK_7);       /* use timer 0 as OS timer */

/*
#define USE_TASK 0
#if USE_TASK > 0
#endif
*/

#endif