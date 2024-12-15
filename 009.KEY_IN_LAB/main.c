#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

/* Key 인식 */

#if 0

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Test #1\n");

	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL,0xff,0x44,24);
	Macro_Write_Block(GPIOB->CRH,0xff,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);

	for(;;)
	{
		// // KEY0이 눌렸으면 LED0를 ON, 안 눌렸으면 OFF
		// if(Macro_Check_Bit_Set(GPIOB->IDR,6) == 0)
		// {
		// 	Macro_Clear_Bit(GPIOB->ODR,8);
		// }
		// else
		// {
		// 	Macro_Set_Bit(GPIOB->ODR,8);
		// }

		// // KEY1이 눌렸으면 LED1를 ON, 안 눌렸으면 OFF
		// if(Macro_Check_Bit_Clear(GPIOB->IDR,7) == 1)
		// {
		// 	Macro_Clear_Bit(GPIOB->ODR,9);
		// }
		// else
		// {
		// 	Macro_Set_Bit(GPIOB->ODR,9);
		// }

		// int key = Macro_Extract_Area(~GPIOB->IDR,0x3,6);
		// LED_Display(key);

		Macro_Write_Block(GPIOB->ODR, 0x3, Macro_Extract_Area(GPIOB->IDR,0x3,6) , 8);
	}

}


#endif

/* Key에 의한 LED Toggling */

#if 0

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");

	int interlock = 1;
	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL,0xff,0x44,24);
	Macro_Write_Block(GPIOB->CRH,0xff,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);


	for(;;)
	{
		// KEY0가 눌릴때마다 LED0의 값을 Toggling
	
		if((interlock !=0) && Macro_Check_Bit_Clear(GPIOB->IDR,6))
		{
			Macro_Invert_Bit(GPIOB->ODR,8);
			interlock = 0;
		}
		else if ((interlock == 0) && Macro_Check_Bit_Set(GPIOB->IDR,6))
		{
			interlock = 1;
		}
	}
}

#endif

#if 1

void Main(void)
{
	int interlock = 1;
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOA->CRL,0xff,0x86,8);
	Macro_Write_Block(GPIOA->ODR,0x3,0x2,2);

	for(;;)
	{
		if((interlock !=0) && Macro_Check_Bit_Clear(GPIOA->IDR,3))
		{
			Macro_Invert_Bit(GPIOA->ODR,2);
			interlock = 0;
		}
		else if ((interlock == 0) && Macro_Check_Bit_Set(GPIOA->IDR,3))
		{
			interlock = 1;
		}
	}
}

#endif