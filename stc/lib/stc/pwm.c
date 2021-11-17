#include "config.h"
#include "pwm.h"

#if PWM_SOFT > 0
u8 __idata pwm_soft_status = 0x00; // status 0:suspend, 1:running
u8 __idata pwm_soft_count[PWM_SOFT];
u8 __idata pwm_soft_high_reload[PWM_SOFT];
u8 __idata pwm_soft_low_reload[PWM_SOFT];

u8 const note_soft_reload_high[] = {125, 118, 112, 106, 100, 94, 89, 84, 79, 75, 71, 67, 63, 59, 56, 53, 50, 47, 45, 42, 40, 37, 35, 33, 32, 30, 28, 27, 25, 24, 22, 21, 20, 19, 18, 17};
u8 const note_soft_reload_low[] = {125, 118, 111, 105, 99, 94, 88, 83, 79, 74, 70, 66, 62, 59, 56, 52, 49, 47, 44, 42, 39, 37, 35, 33, 31, 29, 28, 26, 25, 23, 22, 21, 19, 18, 17, 16};

void start_pwm_soft(void)
{
#if PWM_SOFT_TIMER_MODE_1T > 0
    timer_12x(PWM_SOFT_TIMER);
#endif
    load_timer(PWM_SOFT_TIMER, PWM_SOFT_TIMER_RELOAD);
    start_timer(PWM_SOFT_TIMER);
    enable_timer_interrupt(PWM_SOFT_TIMER, TRUE);
}

void stop_pwm_soft(void)
{
    stop_timer(PWM_SOFT_TIMER);
    enable_timer_interrupt(PWM_SOFT_TIMER, FALSE);
}

void pwm_soft_tick(void) __interrupt(PWM_SOFT_TIMER_ISR)
{
    enter_critical();
#ifdef PWM_SOFT_0
    update_pwm_soft(0);
#endif
#ifdef PWM_SOFT_1
    update_pwm_soft(1);
#endif
#ifdef PWM_SOFT_2
    update_pwm_soft(2);
#endif
#ifdef PWM_SOFT_3
    update_pwm_soft(3);
#endif
#ifdef PWM_SOFT_4
    update_pwm_soft(4);
#endif
#ifdef PWM_SOFT_5
    update_pwm_soft(5);
#endif
#ifdef PWM_SOFT_6
    update_pwm_soft(6);
#endif
#ifdef PWM_SOFT_7
    update_pwm_soft(7);
#endif
    exit_critical();
}
#endif