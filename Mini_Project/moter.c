#include <device_driver.h>

void device_init()
{
    Uart1_Init();
    Clock_Init();
    Macro_Set_Bit(RCC->APB2ENR, 2); // PortA Clock ON
}

void device_execute()
{
    switch (Uart1_Get_Char)
    {
    case S:
        break;
    case F:
        break;
    case R:
        break;
    }
}

void Moter_Stop()
{
    Macro_Set_Bit(GPIOA->ODR, 1);         // PA1(EN) -> High
    Macro_Clear_Area(GPIOA->ODR, 0x3, 2); // PA2(1A),PA3(2A) -> Low
}

void Moter_Forward()
{
    Macro_Set_Bit(GPIOA->ODR, 1);
    Macro_Set_Bit(GPIOA->ODR, 2);   // PA2(1A) -> High
    Macro_Clear_Bit(GPIOA->ODR, 3); // PA3(2A) -> Low
}

void Moter_Reserve()
{
    Macro_Set_Bit(GPIOA->ODR, 1);
    Macro_Clear_Bit(GPIOA->ODR, 2); // PA2(1A) -> Low
    Macro_Set_Bit(GPIOA->ODR, 3);   // PA3(2A) -> High
}