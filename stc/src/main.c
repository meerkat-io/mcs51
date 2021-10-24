#include <stc15.h>
#include <gpio.h>

void main()
{
    GPIO_OUT_PUSH_PULL(P0M1, P0M0, 0);

    u8 count = 0;
    while (1)
    {
        count++;
    }
}