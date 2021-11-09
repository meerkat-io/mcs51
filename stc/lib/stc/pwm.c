#include "config.h"
#include "pwm.h"

#if PWM > 0
u8 __idata pwm_high_reload[PWM];
u8 __idata pwm_low_reload[PWM];
u8 __idata pwm_count[PWM];
u8 __idata pwm_status = 0x00; // status 0:suspend, 1:running

u8 const note_reload_high[] = {125, 118, 112, 106, 100, 94, 89, 84, 79, 75, 71, 67, 63, 59, 56, 53, 50, 47, 45, 42, 40, 37, 35, 33, 32, 30, 28, 27, 25, 24, 22, 21, 20, 19, 18, 17};
u8 const note_reload_low[] = {125, 118, 111, 105, 99, 94, 88, 83, 79, 74, 70, 66, 62, 59, 56, 52, 49, 47, 44, 42, 39, 37, 35, 33, 31, 29, 28, 26, 25, 23, 22, 21, 19, 18, 17, 16};

void start_pwm(void)
{
    #ifdef PWM_TIMER_MODE_1T
    timer_12x(PWM_TIMER);
    #endif
    load_timer(PWM_TIMER, PWM_RELOAD);
    start_timer(PWM_TIMER);
    enable_timer_interrupt(PWM_TIMER, TRUE);
}

void stop_pwm(void)
{
    stop_timer(PWM_TIMER);
    enable_timer_interrupt(PWM_TIMER, FALSE);
}

void pwm_tick(void) __interrupt(PWM_TIMER_ISR)
{
    enter_critical();
#ifdef PWM_0
    update_pwm(0);
#endif
#ifdef PWM_1
    update_pwm(1);
#endif
#ifdef PWM_2
    update_pwm(2);
#endif
#ifdef PWM_3
    update_pwm(3);
#endif
#ifdef PWM_4
    update_pwm(4);
#endif
#ifdef PWM_5
    update_pwm(5);
#endif
#ifdef PWM_6
    update_pwm(6);
#endif
#ifdef PWM_7
    update_pwm(7);
#endif
    exit_critical();
}

#endif