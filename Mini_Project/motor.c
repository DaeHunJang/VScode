#include <device_driver.h>

void device_init()
{
    Uart1_Init(115200);
    Uart1_RX_Interrupt_Enable(1);
    Key_ISR_Enable(1);
    Clock_Init();
    // PortA Clock ON
    Macro_Set_Bit(RCC->APB2ENR, 2);
    // PA1(EN),PA2(1A),PA3(2A) ->General Purpose Output Push-Pull
    Macro_Write_Block(GPIOA->CRL, 0xfff, 0x222, 4);
    Uart1_Printf("Motor Control System Ready\n");
}

void device_execute(char recevied_command)
{    
    switch (recevied_command)
    {
    case 'S':
        Motor_Stop();
        break;
    case 'F':
        Motor_Forward();
        break;
    case 'R':
        Motor_Reserve();
        break;
    default:

        break;
    }
}

void Motor_Stop(void)
{
    Macro_Set_Bit(GPIOA->ODR, 1);         // PA1(EN) -> High
    Macro_Clear_Area(GPIOA->ODR, 0x3, 2); // PA2(1A),PA3(2A) -> Low
    Uart1_Printf("Motor Stopped\n"); 
}

void Motor_Forward(void)
{
    Macro_Set_Bit(GPIOA->ODR, 1);
    //Macro_Set_Bit(GPIOA->ODR, 2);   // PA2(1A) -> High
    //Macro_Clear_Bit(GPIOA->ODR, 3); // PA3(2A) -> Low
    Macro_Write_Block(GPIOA->ODR,0x3,0x1,2);
    Uart1_Printf("Motor Forward\n");
}

void Motor_Reserve(void)
{
    Macro_Set_Bit(GPIOA->ODR, 1);
    //Macro_Clear_Bit(GPIOA->ODR, 2); // PA2(1A) -> Low
    //Macro_Set_Bit(GPIOA->ODR, 3);   // PA3(2A) -> High
    Macro_Write_Block(GPIOA->ODR,0x3,0x2,2);
    Uart1_Printf("Motor Reverse\n"); 
}