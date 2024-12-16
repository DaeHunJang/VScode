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
		for(;;)
		{
			if(Macro_Check_Bit_Set(USART1->SR,5)) break;
		}
		// while (Macro_Check_Bit_Clear(USART1->SR,5)); -->while문 안에 원하는 조건에 부정
		char data = USART1->DR;
		for(;;)
		{
			if(Macro_Check_Bit_Set(USART1->SR,7)) break;
		}
		USART1->DR = data;
	}
}