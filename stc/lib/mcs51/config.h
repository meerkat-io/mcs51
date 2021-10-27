#ifndef CONFIG_H
#define CONFIG_H

#include "stc15.h"                             /* the mcu to use */

#define OSC             5529600L               /* main osc frequency: 5529600L 11059200L 22118400L 6000000L 12000000L 24000000L*/
#define OS_TIMER        1                      /* os timer interrupt */ 
#define TIMER_DIVISION  16                     /* timer frequency division */
#define TICK_FREQUENCY  100                    /* ticker frequency */

#define USE_TASK 0
#if USE_TASK > 0
#endif

#endif