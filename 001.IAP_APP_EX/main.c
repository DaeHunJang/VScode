#include "device_driver.h"

#if 1

void Main(void)
{
	int value;

	Uart_Init(115200);

	for(value = 0; value <= 15; value++)
	{
		Uart_Printf("%d\n", value);
	}

	Uart_Printf("END\n");
}

#endif

#if 0

void Main(void)
{
	int value = 10;

	Uart_Init(115200);

	Uart_Printf("WILLTEK\n");
	Uart_Printf("VALUE=%d\n", value = 10);
	Uart_Printf("%d, %c, %f\n", 100, 'A', 3.14);
	Uart_Printf("Bye~\n");
}

#endif
