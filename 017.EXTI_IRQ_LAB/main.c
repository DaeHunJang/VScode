#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 0;
}

void Main(void)
{
	Sys_Init();
	Uart1_Printf("EXTI Test\n");

	// AFIO, Port-B Clock Enable

	// PB[7:6]을 입력으로 선언

	// PB[7:6]을 EXTI 소스로 설정하고 Falling edge 선택, EXTI[7:6] 인터럽트 허용

	// EXTI[7:6] Pending Clear 및 NVIC의 인터럽트 Pending clear

	// EXTI9_5 인터럽트 허용

	for(;;)
	{
		LED_Display(1);
		TIM2_Delay(500);
		LED_Display(2);
		TIM2_Delay(500);
	}
}
