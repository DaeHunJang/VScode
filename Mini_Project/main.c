#include <stdio.h>

void main(void)
{
    device_init();

    for(;;)
    {
        device_execute();
    }
}