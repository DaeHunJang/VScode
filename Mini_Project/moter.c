#include <stdio.h>
#include <moter.h>

void moter_init()
{
    //PA->clock ON
    Macro_Set_Bit(RCC->APB2ENR, 2);

    //PA1(EN), PA2(1A) ,PA3(2A) GPIO Output Set
    Macro_Write_Block(GPIOA->CRL,0xfff,0x733,4); //PA1->General purpose / open-drain, PA2 ->General purpose / Push-pull, PA3 -> General purpose / Push-pull
}


void moter_execute()
{

}

void moter_S()
{
    Macro_Set_Bit(GPIOA->ODR,1);    //PA1 High
}

void moter_F()
{
    Macro_Set_Bit(GPIOA->ODR,1);    //PA1 High
    Macro_Set_Bit(GPIOA->ODR,2);    //PA2(1A) High
    Macro_Clear_Bit(GPIOA->ODR,3);  //PA3(2A) Low
}

void moter_R()
{
    Macro_Set_Bit(GPIOA->ODR,1);    //PA1 High
    Macro_Clear_Bit(GPIOA->ODR,2);    //PA2(1A) Low
    Macro_Set_Bit(GPIOA->ODR,3);  //PA3(2A) High
}