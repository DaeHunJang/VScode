#include "device_driver.h"

#if 0

void Main(void)
{
	RCC->APB2ENR |= (1<<3);
	
	// LED0, LED1 General Output으로 설정
	// CNF1,CNF0	-> Open-drain
	//  0	 1
	// MODE1,MODE2	-> output speed 2MHz(LED는 출력속도가 낮아도 됨)
	//  1	 0
	// GPIOB_CRH -> 0110 0110
	GPIOB->CRH = 0x66 << 0;

	// LED0, LED1 ON,OFF 설정
	// LED0, LED1 -> 0이면 ON / 1이면 OFF
	// LED0-> PB8, LED1->PB9 / 0x1<<8 -> LED0 ON, LED1 OFF 설정정
	GPIOB->ODR = 0x1 << 8;
}

#endif

#if 0

void Main(void)
{
	/* 이 부분은 임의로 바꾸지 마시오 */
	RCC->APB2ENR |= (1<<3);

	/* 비트 연산을 이용하여 LED0을 ON, LED1을 OFF로 하는 코드를 설계하시오 */

	// (GPIOB->CRH &~(0xff<<0)) -> 0번째bit부터 8bit를 0으로 변경 (&~) (CRH[8:0])
	// | (0x66<<0) 				-> 0으로 변경한 8bit 공간을 0110 0110 으로 변경
	GPIOB->CRH = (GPIOB->CRH &~(0xff<<0)) | (0x66<<0); 

	// (GPIOB->ODR &~(0x3<<8))	-> 8번째bit부터 2bit를 0으로 변경 (ODR[9:8])
	// | (0x2<<8)				-> 0으로 변경한 2bit 공간을 10 으로 변경
	//LED0 ON / LED1 OFF
	GPIOB->ODR = (GPIOB->ODR &~(0x3<<8)) | (0x2<<8);
}

#endif



/* Bit 연산 Macro 활용 */

#if 0

void Main(void)
{
	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* Macro를 이용하여 LED0을 ON, LED1을 OFF로 하는 코드를 설계하시오 */
	Macro_Write_Block(GPIOB->CRH,0xff,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x1,8);


}

#endif


/* Bit 연산 Macro 활용 LED Toggling */

#if 0

void Main(void)
{
	volatile int i;

	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* 매크로를 이용하여 초기에 LED 모두 OFF */
	Macro_Write_Block(GPIOB->CRH,0xff,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);


	for(;;)
	{
	/* LED 반전 및 Delay, Delay는 0x80000으로 설정 */
	/*
	Macro_Set_Area(GPIOB->ODR,0x3,8);
	for(i=0;i<0x80000;i++);
	Macro_Clear_Area(GPIOB->ODR,0x3,8);
	for(i=0;i<0x80000;i++);
	*/
	Macro_Invert_Area(GPIOB->ODR,0x3,8);
	for(i=0;i<0x80000;i++);
	}
}

#endif

#if 0
//PA2 ->led blink
void Main(void)
{
	volatile int i;

	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOA->CRL,0xf,0x6,8);
	Macro_Write_Block(GPIOA->ODR,1,1,2);

	for(;;)
	{
		Macro_Invert_Area(GPIOA->ODR,0x1,2);
		for(i=0;i<0x80000;i++);
	}
}
#endif