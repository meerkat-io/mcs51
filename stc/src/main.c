#include <os.h>
#include <pwm.h>

void task0(void);
void task1(void);
void (* const tasks[OS_TASKS])(void) = {task0};

const u8 HALF_DUTY = 127;

void main(void)
{
    enter_critical();

    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 2, 6);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 2, 7);

    //set_duty(0, HALF_DUTY);
    //set_tone(1, 440);
    //start_pwm();
    P26 = 1;
    P27 = 1;
   
    os_start();
}

void task0(void)
{
    while (1)
    {
        //P27 = 0;
        //os_wait(15);
        //P27 = 1;
        //os_wait(15);
        //P27 = 0;
        //os_wait(15);
        //P27 = 1;
        //os_wait(15);
        //P27 = 0;
        //os_wait(15);
        //P27 = 1;
        //os_wait(100);

        P27 = !P27;
        os_wait(100);
    }
    //return;
}

void task1(void)
{
    while (1)
    {
        P26 = 0;
        os_wait(100);
        P26 = 1;
        os_wait(100);
    }
}