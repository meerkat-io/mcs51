#include <os.h>
#include <pwm.h>

void task0(void);
void task1(void);
void (* const tasks[OS_TASKS])(void) = {task0, task1};

const u8 HALF_DUTY = 127;

void main(void)
{
    enter_critical();

    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 3, 0);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 3, 1);

    set_duty(0, HALF_DUTY);
    set_tone(1, 440);
    start_pwm();
   
    os_start();
}

void task0(void)
{
    while (1)
    {
        P30 = 1;
        os_wait(50);
        P30 = 0;
        os_wait(100);
    }
}

void task1(void)
{
    while (1)
    {
        P31 = 1;
        os_wait(100);
        P31 = 0;
        os_wait(50);
    }
}