#include <os.h>

void main()
{
    gpio_output_push_pull(0, 0);

    u8 count = 0;
    while (1)
    {
        count++;
    }
}

void task0()
{
}

void task1()
{
    
}