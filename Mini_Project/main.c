#include "device_driver.h"


void Main(void)
{
	device_init();

	for(;;)
	{
		device_execute();
	}
}
