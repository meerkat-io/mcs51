#include <os.h>

void task0(void);
void task1(void);
void (* const tasks[OS_TASKS])(void) = {task0, task1};

void main(void)
{
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 0);

    os_start();
}

void task0(void)
{
    while (1)
    {
        os_wait(100);
    }
}

void task1(void)
{
    while (1)
    {
        os_wait(30);
    }
}