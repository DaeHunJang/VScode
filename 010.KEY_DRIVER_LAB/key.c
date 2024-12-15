#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
}

int Key_Get_Pressed(void)
{
	return Macro_Extract_Area(~GPIOB->IDR, 0x3,6);
}

void Key_Wait_Key_Released(void)
{
	for(;;)
	{
		if(Key_Get_Pressed() == 0) return;
	}

}

int Key_Wait_Key_Pressed(void)
{
	for(;;)
	{
		int r = Key_Get_Pressed();
		if(r !=0) return r;
	}
}
