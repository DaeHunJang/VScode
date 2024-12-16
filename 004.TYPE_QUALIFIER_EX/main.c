#include "device_driver.h"

#if 0

// 컴파일러의존성을 없애야 하기떄문에 int-> volatile unsigned long로 바꿔줘야함
// 주변장치는 반드시 volatile unsigned 를 선언 해 주어야 함
#define RCC_APB2ENR   (*(unsigned long*)0x40021018)

#define GPIOB_CRH      (*(volatile unsigned long*)0x40010C04)
#define GPIOB_ODR      (*(volatile unsigned long*)0x40010C0C)

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #1\n");
	RCC_APB2ENR |= (1<<3);

	GPIOB_CRH = 0x66 << 0;

	for(;;)
	{
		GPIOB_ODR = 0x0 << 8;	// LED0, LED1 ON
		for(i=0; i<0x40000; i++);
		GPIOB_ODR = 0x3 << 8;	// LED0, LED1 OFF
		for(i=0; i<0x40000; i++);
	}
}

#endif

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #1\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #2\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define TIMER   (*(volatile unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #3\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define RCC_APB2ENR   (*(volatile unsigned long*)0x40021018)

#define GPIOB_CRH      (*(volatile unsigned long*)0x40010C04)
#define GPIOB_ODR      (*(volatile unsigned long*)0x40010C0C)

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #2\n");
	RCC_APB2ENR |= (1<<3);

	GPIOB_CRH = 0x66 << 0;

	for(;;)
	{
		GPIOB_ODR = 0x0 << 8;
		for(i=0; i<0x40000; i++);
		GPIOB_ODR = 0x3 << 8;
		for(i=0; i<0x40000; i++);
	}
}

#endif
