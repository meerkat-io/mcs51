#include <os.h>

void main()
{
    GPIO_OUTPUT_PUSH_PULL(0, 0);

    u8 count = 0;
    while (1)
    {
        count++;
    }
}