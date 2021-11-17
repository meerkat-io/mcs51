#ifndef PWM_H
#define PWM_H

#include "os.h"

/**********************************************
 *  128Hz 256 resolution PWM
 *  Tone & Note (available freq range : 129 ~ 32767)
    Note	    Freq(Hz)	Length(cm)  ReloadH ReloadL
    C4	        261.63	    131.87      125     125
    C#4/Db4 	277.18	    124.47      118     118
    D4	        293.66	    117.48      112     111
    D#4/Eb4 	311.13	    110.89      106     105     
    E4	        329.63	    104.66      100     99
    F4	        349.23	    98.79       94      94
    F#4/Gb4 	369.99	    93.24       89      88
    G4	        392.00	    88.01       84      83
    G#4/Ab4 	415.30	    83.07       79      79
    A4	        440.00	    78.41       75      74
    A#4/Bb4 	466.16	    74.01       71      70
    B4	        493.88	    69.85       67      66
    C5	        523.25	    65.93       63      62
    C#5/Db5 	554.37	    62.23       59      59
    D5	        587.33	    58.74       56      56
    D#5/Eb5 	622.25	    55.44       53      52
    E5	        659.25	    52.33       50      49
    F5	        698.46	    49.39       47      47
    F#5/Gb5 	739.99	    46.62       45      44
    G5	        783.99	    44.01       42      42
    G#5/Ab5 	830.61	    41.54       40      39
    A5	        880.00	    39.20       37      37
    A#5/Bb5 	932.33	    37.00       35      35
    B5	        987.77	    34.93       33      33
    C6	        1046.50	    32.97       32      31      
    C#6/Db6 	1108.73	    31.12       30      29
    D6	        1174.66	    29.37       28      28
    D#6/Eb6 	1244.51	    27.72       27      26
    E6	        1318.51	    26.17       25      25
    F6	        1396.91	    24.70       24      23
    F#6/Gb6 	1479.98	    23.31       22      22
    G6	        1567.98	    22.00       21      21
    G#6/Ab6 	1661.22	    20.77       20      19
    A6	        1760.00	    19.60       19      18
    A#6/Bb6 	1864.66	    18.50       18      17
    B6	        1975.53	    17.46       17      16
 * *****************************************/

#if PWM_SOFT > 0
#define update_pwm_soft(pwm_soft_index)                                                 \
   {                                                                                    \
      if ((pwm_soft_status & BIT_MASK_##pwm_soft_index) != 0)                           \
      {                                                                                 \
         if (pwm_soft_count[pwm_soft_index] == 0)                                       \
         {                                                                              \
            if (PWM_SOFT_##pwm_soft_index == PWM_LOW)                                   \
            {                                                                           \
               pwm_soft_count[pwm_soft_index] = pwm_soft_high_reload[pwm_soft_index];   \
               PWM_SOFT_##pwm_soft_index = PWM_HIGH;                                    \
            }                                                                           \
            else                                                                        \
            {                                                                           \
               pwm_soft_count[pwm_soft_index] = pwm_soft_low_reload[pwm_soft_index];    \
               PWM_SOFT_##pwm_soft_index = PWM_LOW;                                     \
            }                                                                           \
         }                                                                              \
         else                                                                           \
         {                                                                              \
            pwm_soft_count[pwm_soft_index]--;                                           \
         }                                                                              \
      }                                                                                 \
   }

#define set_pwm_soft_duty(pwm_soft_index, duty)                  \
   {                                                             \
      pwm_soft_high_reload[pwm_soft_index] = duty;               \
      pwm_soft_low_reload[pwm_soft_index] = 255 - duty;          \
      pwm_soft_status |= BIT_MASK_##pwm_soft_index;              \
   }
#define set_pwm_soft_duty_on(pwm_soft_index) pwm_soft_status &= ~BIT_MASK_##pwm_soft_index, PWM_SOFT_##pwm_soft_index = PWM_HIGH
#define set_pwm_soft_duty_off(pwm_soft_index) pwm_soft_status &= ~BIT_MASK_##pwm_soft_index, PWM_SOFT_##pwm_soft_index = PWM_LOW
#define set_tone_soft(pwm_soft_index, freq)                                                      \
   {                                                                                             \
      pwm_soft_status |= BIT_MASK_##pwm_soft_index;                                              \
      u16 reload = 0xffff / freq;                                                                \
      pwm_soft_high_reload[pwm_soft_index] = (u8)(reload / 2);                                   \
      pwm_soft_low_reload[pwm_soft_index] = (u8)(reload - pwm_soft_high_reload[pwm_soft_index]); \
   }
#define unset_tone_soft(pwm_soft_index) pwm_soft_status &= ~BIT_MASK_##pwm_soft_index, PWM_##pwm_soft_index = PWM_LOW
#define play_note_soft(pwm_soft_index, note_soft_index)                               \
   {                                                                                  \
      pwm_soft_status |= BIT_MASK_##pwm_soft_index;                                   \
      pwm_soft_high_reload[pwm_soft_index] = note_soft_reload_high[note_soft_index];  \
      pwm_soft_low_reload[pwm_soft_index] = note_soft_reload_low[note_soft_index];    \
   }
#define stop_note_soft(pwm_soft_index) pwm_soft_status &= ~BIT_MASK_##pwm_soft_index

extern u8 __idata pwm_soft_status;
extern u8 __idata pwm_soft_count[];
extern u8 __idata pwm_soft_high_reload[];
extern u8 __idata pwm_soft_low_reload[];
extern u8 const note_soft_reload_high[];
extern u8 const note_soft_reload_low[];

extern void pwm_soft_start(void);
extern void pwm_soft_stop(void);
extern void pwm_soft_tick(void) __interrupt(PWM_SOFT_TIMER_ISR);
#endif

#endif