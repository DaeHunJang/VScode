#include "device_driver.h"

void LED_Init(void)
{
	/* 다음 코드는 수정하지 마시오 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	// LED를 사용 하기 위해 init
	Macro_Write_Block(GPIOB->CRH,0xff,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);
}

void LED_Display(unsigned int num)
{
	// LED0,LED1이 ON 되려면 기존에는 0이지만 num에 따라 LED ON/OFF를 반전
	// Macro_Extract_Area(~num,0x3,0)
	// num 	-> 00(둘다 OFF)	01(LED1만 ON),	10(LED0만 ON), 11, 100, 101, 110, 111 ~
	// ~num	-> 11			10				01 			   00 ~
	unsigned int putnum = Macro_Extract_Area(~num,0x3,0);
	Macro_Write_Block(GPIOB->ODR,0x3,putnum,8);
	// 한줄로 : Macro_Write_Block(GPIOB->ODR,0x3,Macro_Extract_Area(~num,0x3,0),8);
}

void LED_All_On(void)
{
	Macro_Clear_Area(GPIOB->ODR,0x3,8);
}

void LED_All_Off(void)
{
	Macro_Set_Area(GPIOB->ODR,0x3,8);
}
