#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

void Main(void)
{
	Sys_Init();
	Uart_Printf("UART Echo-Back Test\n");

	for(;;)
	{
		// 받은 글자를 다시 UART로 출력한다


	}
}