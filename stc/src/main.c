#include <os.h>

void main(void)
{
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 0, 0);
    clock_divide(1);

    u8 count = 0;
    while (1)
    {
        count++;
    }
}

void task0(void)
{
}

void task1(void)
{
}