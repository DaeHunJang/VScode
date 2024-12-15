#include "device_driver.h"

#define LCDW (320)
#define LCDH (240)
#define X_MIN (0)
#define X_MAX (LCDW - 1)
#define Y_MIN (0)
#define Y_MAX (LCDH - 1)

#define TIMER_PERIOD (10)

static unsigned short color[] = {RED, YELLOW, GREEN, BLUE, WHITE, BLACK};

extern volatile int TIM4_expired; // isr에서 갱신
extern volatile int Jog_key_in;
extern volatile int Jog_key;

void Main(void)
{
	Uart_Printf("Game Project\n"); // 터미널에 인쇄?>

	Lcd_Init();
	Jog_Poll_Init();
	Jog_ISR_Enable(1);
	Uart1_RX_Interrupt_Enable(1);
	Lcd_Clr_Screen(); // 하드웨어 설정 건드리지 말기

	int frog_pos_x = 70, frog_pos_y = Y_MAX - 10;
	// int car_pos_x = 0, car_pos_y = (LCDH / 2) - 5;
	// int car_color = 1;
	int tick_count = 0;
	int flag = 0;

	int road_x = 0, road_y = 0;
	TIM4_Repeat_Interrupt_Enable(1, TIMER_PERIOD * 10);
	Lcd_Draw_Box(frog_pos_x, frog_pos_y, 10, 10, color[0]); // 그림함수
															// Lcd_Draw_Box(car_pos_x, car_pos_y, 20, 20, color[0]);

	int i;
	for (i = 100; i < Y_MAX - 10; i++)
	{
		Lcd_Draw_Box(40, i, 10, 10, color[1]);
	}
	for (i = 160; i < Y_MAX - 10; i++)
	{
		Lcd_Draw_Box(100, i, 10, 10, color[1]);
	}
	for (i = 0; i <= 90; i++)
	{
		Lcd_Draw_Box(190, i, 10, 10, color[1]);
	}
	for (i = 0; i <= 150; i++)
	{
		Lcd_Draw_Box(250, i, 10, 10, color[1]);
	}
	Lcd_Draw_Box(40, 100, 160, 10, color[1]);
	Lcd_Draw_Box(100, 150, 160, 10, color[1]);

	Lcd_Draw_Box(190, 5, 60, 5, color[4]);
	for (;;)
	{
		if (Jog_key_in)
		{
			Uart_Printf("KEY = %d\n", Jog_key);

			Lcd_Draw_Box(frog_pos_x, frog_pos_y, 10, 10, color[5]);

			if (Jog_key == 2 && frog_pos_x > X_MIN)
				frog_pos_x -= 10;
			if (Jog_key == 3 && frog_pos_x < X_MAX - 10)
				frog_pos_x += 10;
			if (Jog_key == 0 && frog_pos_y > Y_MIN)
				frog_pos_y -= 10;
			if (Jog_key == 1 && frog_pos_y < Y_MAX - 10)
				frog_pos_y += 10;

			Lcd_Draw_Box(frog_pos_x, frog_pos_y, 10, 10, color[0]);
			Jog_key_in = 0;
		}

		if (TIM4_expired)
		{
			tick_count++;

			if (tick_count > 50)
			{
				Lcd_Draw_Box(0, 80, 320, 100, color[3]);
				flag = 1;
			}

			TIM4_expired = 0;
		}

		if ((frog_pos_x < 45 && frog_pos_y > 95) ||
			(frog_pos_x < 195 && frog_pos_y < 95) ||
			(frog_pos_x > 95 && frog_pos_y > 155) ||
			(frog_pos_x > 245 && frog_pos_y < 155))
		{
			Uart_Printf("game over\n");
			return;
		}

		if ((frog_pos_x > 190 && frog_pos_x < 250 && frog_pos_y < 4))
		{
			char score;
			if (tick_count < 1000)
			{
				score = 'S';
			}
			else if (tick_count < 2000)
			{
				score = 'A';
			}
			else if (tick_count < 3000)
			{
				score = 'B';
			}
			else if (tick_count < 4000)
			{
				score = 'C';
			}
			else
			{
				score = 'F';
			}
			Uart_Printf("succuss, score: %c\n",score);
			return;
		}
	}
}
