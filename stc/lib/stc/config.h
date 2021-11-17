#ifndef CONFIG_H
#define CONFIG_H

#include "stc15.h"                                /* the mcu to use */

#define OSC                11059200L              /* main osc frequency: 5529600L 11059200L 22118400L 6000000L 12000000L 24000000L*/
#define TIMER_DIVISION     1                      /* timer frequency division */

#define TASKS                2                 /* task count, max 8 custom tasks */
#define TASK_TIMER              0                 /* os timer, default : timer 0 */
#define TASK_TIMER_ISR          1                 /* rtos timer interrupt (for timer 0) */ 
#define TASK_TIMER_MODE_1T      0                 /* use 1T timer mode: 1 yes, 0 no */
#define TASK_TICK_FREQUENCY       100               /* ticker frequency Hz */
#if TASK_TIMER_MODE_1T > 0                        /* 16 bit auto reload */
#define TASK_TIMER_RELOAD   (65535 - OSC/TIMER_DIVISION/TASK_TICK_FREQUENCY)
#else
#define TASK_TIMER_RELOAD   (65535 - OSC/12/TIMER_DIVISION/TASK_TICK_FREQUENCY)
#endif

#define PWM_OUPUT_INVERT        1                 /* 1 is on and 0 is off, if invert 0 is on and 1 is off */
#if PWM_OUPUT_INVERT == 0
#define PWM_HIGH 1
#define PWM_LOW 0
#else
#define PWM_HIGH 0
#define PWM_LOW 1
#endif

#define PWM_SOFT                3                 /* soft pwm/tone pin count */
#define PWM_SOFT_0              P07               /* pwm pin 0 */
#define PWM_SOFT_1              P06               /* pwm pin 1 */
#define PWM_SOFT_2              P54               /* pwm pin 1 */
#define PWM_SOFT_TIMER          1                 /* pwm timer, default : timer 1 */
#define PWM_SOFT_TIMER_ISR      3                 /* pwm timer interrupt (for timer 1) */ 
#define PWM_SOFT_TIMER_MODE_1T  1                 /* use 1T timer mode: 1 yes, 0 no */
#if PWM_SOFT_TIMER_MODE_1T > 0                    /* 8 bit auto reload */
#define PWM_SOFT_TIMER_RELOAD   (65535 - OSC/TIMER_DIVISION/65536)
#else
#define PWM_SOFT_TIMER_RELOAD   (65535 - OSC/12/TIMER_DIVISION/65536)
#endif

#endif