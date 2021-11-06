#include <os.h>

void task0(void);
void task1(void);
void (* const tasks[OS_TASKS])(void) = {task0, task1};

void main(void)
{
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 3, 0);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 3, 1);
   
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