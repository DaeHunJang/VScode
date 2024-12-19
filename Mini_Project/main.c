#include "device_driver.h"

char received_command;

void Main(void)
{
	device_init();
	
	for(;;)
	{
		received_command = Uart1_Get_Char();
		device_execute(received_command);
		Uart1_Printf("%c\n",received_command);
	}
}
