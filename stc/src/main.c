#include <os.h>
#include <pwm.h>

void task0(void);
void task1(void);
void (*const tasks[OS_TASKS])(void) = {task0}; //, task1};

void main(void)
{
    enter_critical();

    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 0);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 1);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 2);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 3);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 4);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 5);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 6);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 7);

    P00 = 1;
    P01 = 1;
    P02 = 1;
    P03 = 1;
    P04 = 1;
    P05 = 1;
    P06 = 1;
    P07 = 1;

    u8 duty = 63;
    //set_pwm_soft_duty_on(0);
    set_pwm_soft_duty(0, duty);
    //set_tone_soft(1, 440);
    pwm_soft_start();

    os_start();
}
/*
void pwm_tick(void) __interrupt(PWM_SOFT_TIMER_ISR)
{
    PWM_SOFT_0 = PWM_HIGH;
}*/

void task0(void)
{
    while (1)
    {
        P00 = 0;
        task_sleep(10);
        P00 = 1;
        task_sleep(10);
        P00 = 0;
        task_sleep(10);
        P00 = 1;
        task_sleep(10);
        P00 = 0;
        task_sleep(10);
        P00 = 1;
        task_sleep(100);
    }
}

void task1(void)
{
    while (1)
    {
        P01 = 0;
        task_sleep(50);
        P01 = 1;
        task_sleep(50);
    }
}