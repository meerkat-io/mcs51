#include <task.h>
#include <pwm.h>

void task0(void);
void task1(void);
void (*const tasks[TASKS])(void) = {task0, task1};

void main(void)
{
    enter_critical();

    clock_divide(TIMER_DIVISION);

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

    set_pwm_soft_duty(0, 20);
    set_pwm_soft_duty(1, 240);
    pwm_soft_start();

    reset_timer();

    task_start();
    task_run();
}

void task0(void)
{
    P00 = !P00;
    task_sleep(10);
}

const u8 song[30] = {24, 100, 24, 100, 28, 100, 28, 100, 29, 100, 29, 100, 28, 28, 100, 27, 100, 27, 100, 26, 100, 26, 100, 25, 100, 25, 100, 24, 24, 100};

void task1(void)
{
    static u8 index = 0;
    u8 sleep = 50;
    if (song[index] == 100) {
        stop_note_soft(2);
        sleep = 10;
    } 
    else
    {
        play_note_soft(2, song[index]);
    }
    index++;
    if (index == 30) {
        index = 0;
    }
    task_sleep(sleep);
}