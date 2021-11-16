#ifndef CONFIG_H
#define CONFIG_H

#include "stc15.h"                                /* the mcu to use */

#define OSC                11059200L              /* main osc frequency: 5529600L 11059200L 22118400L 6000000L 12000000L 24000000L*/
#define TIMER_DIVISION  1                         /* timer frequency division */

#define OS_TIMER           0                      /* os timer, default : timer 0 */
#define OS_TIMER_ISR       1                      /* rtos timer interrupt (for timer 0) */ 
#define OS_TIMER_MODE_1T   0                      /* use 1T timer mode: 1 yes, 0 no */
#define OS_TICK_FREQUENCY  100                    /* ticker frequency Hz */
#if OS_TIMER_MODE_1T > 0                          /* 16 bit auto reload */
#define OS_TIMER_RELOAD   (65535 - OSC/TIMER_DIVISION/OS_TICK_FREQUENCY)
#else
#define OS_TIMER_RELOAD   (65535 - OSC/12/TIMER_DIVISION/OS_TICK_FREQUENCY)
#endif
#define OS_TASKS                1                 /* task count, max 8 custom tasks */
#define TASK_STACK_SIZE         16                /* stack size pro task, 2 reserved for PC */

#define PWM                     0                 /* soft pwm/tone pin count */
#define PWM_0                   P30               /* pwm pin 0 */
#define PWM_1                   P31               /* pwm pin 1 */
#define PWM_TIMER               1                 /* pwm timer, default : timer 1 */
#define PWM_TIMER_ISR           3                 /* pwm timer interrupt (for timer 1) */ 
#define PWM_TIMER_MODE_1T       1                 /* use 1T timer mode: 1 yes, 0 no */
#if PWM_TIMER_MODE_1T > 0                         /* 8 bit auto reload */
#define PWM_RELOAD   (65535 - OSC/TIMER_DIVISION/65536)
#else
#define PWM_RELOAD   (65535 - OSC/12/TIMER_DIVISION/65536)
#endif

#endif