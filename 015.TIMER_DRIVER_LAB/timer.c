#include "device_driver.h"

#define	TIM2_TICK		20					//20usec
#define	TIM2_FREQ		(1000000./TIM2_TICK)	// Hz -> double type
#define TIM2_ARR_MAX	0xffff
#define TIM2_1ms_PLS	(1000/TIM2_TICK)

#define	TIM4_TICK		20					//20usec
#define	TIM4_FREQ		(1000000./TIM4_TICK)	// Hz -> double type
#define TIM4_ARR_MAX	0xffff
#define TIM4_1ms_PLS	(1000/TIM4_TICK)

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);
	//1.
	// TIM2 CR1 설정: down count, one pulse
	// 비트 연산이 아닌 대입연산을 할때는 원하는 비트만 1로 하고 설정 안한 비트는 0
	// TIM2->CR1 = ((1 << 4) | (1 << 3));
	TIM2->CR1 = (TIM2->CR1 & ~((0x1f << 5) | (0x3 << 1))) | ((1 << 4) | (1 << 3));
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (72000000 / 50000) - 1;
	// ARR 초기값 설정 => 최대값 0xFFFF 설정
	TIM2->ARR = 0xffff;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR,0);
	// TIM2 start
	TIM2->CR1 |= (1 << 0);

	//2.
	// TIM2->PSC = (int)(TIMXCLK/TIM2_FREQ + 0.5) -1;
	// TIM2->ARR = TIM2_ARR_MAX;
	// Macro_Set_Bit(TIM2->EGR,0);	// TIM2->EGR |= 1<<0;

	// TIM2->CR1 = (1<<4 | 1<<3 | 1<<0);

}

unsigned int TIM2_Stopwatch_Stop(void)
{
	// 1.
	unsigned int time;
	// TIM2 stop
	TIM2->CR1 &= ~(1 << 0);
	// CNT 초기 설정값 (0xffff)와 현재 CNT의 펄스수 차이를 구하고
	time = TIM2->ARR - TIM2->CNT;
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	time = time * 20;
	// 계산된 time 값을 리턴(단위는 usec)
	return time;

	//2.
	// Macro_Clear_Bit(TIM2->CR1,0);
	// return (TIM2_ARR_MAX - TIM2->CNT) * TIM2_TICK;

}

void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (1<<4 | 1<<3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (int)(TIMXCLK/TIM2_FREQ + 0.5) -1;
	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	TIM2->ARR = time*TIM2_1ms_PLS;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR,0);
	// Update Interrupt Pending Clear
	TIM2->SR &= ~(1<<0);
	// Update Interrupt Enable
	TIM2->DIER |= (1<<0);
	// TIM2 start
	TIM2->CR1 |= (1 << 0);
	// Wait timeout
	while(!(Macro_Check_Bit_Set(TIM2->SR,0)));
	// Stop and Power off
	Macro_Clear_Bit(TIM2->CR1, 0);
	Macro_Clear_Bit(TIM2->DIER, 0);
}

void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	// TIM4 CR1: ARPE=0, down counter, repeat mode
	TIM4->CR1 = 1<<4;
	// PSC(50KHz),  ARR(reload시 값) 설정
	TIM4->PSC = (int)(TIMXCLK/TIM2_FREQ + 0.5) -1;
	TIM4->ARR = time*TIM4_1ms_PLS;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM4->EGR,0);
	// Update Interrupt Pending Clear
	TIM4->SR &= ~(1<<0);
	// Update Interrupt Enable
	TIM4->DIER |= (1<<0);
	// TIM4 start
	TIM4->CR1 |= (1 << 0);
}

int TIM4_Check_Timeout(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴
	if(Macro_Check_Bit_Set(TIM4->SR,0)){
		TIM4->SR &= ~(1<<0);
		 return 1;
	 }
	return 0;
}

void TIM4_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
	Macro_Clear_Bit(TIM4->DIER, 0);
	Macro_Clear_Bit(RCC->APB1ENR, 2);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = 50 * time;
}
