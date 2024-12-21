#include "device_driver.h"

char received_command;
int speed_level = 50; // 기본 속도 (%)
extern volatile int Uart1_Rx_In;
extern volatile int Uart1_Rx_Data;

void Main(void)
{
    device_init();
    Uart1_Printf("Motor Control System Ready\n");

    for(;;)
    {
        int key_pressed = Key_Get_Pressed();
        
        if (key_pressed == 1) // Key0: UART 제어
        {
            if (Uart1_Rx_In)
            {
                received_command = Uart1_Rx_Data;
                Uart1_Rx_In = 0;
                if (received_command >= '1' && received_command <= '8')
                {
                    speed_level = (received_command - '0') * 10;
                    Uart1_Printf("Speed Level: %d\n", speed_level);
                }
                else
                {
                    device_execute(received_command, speed_level);
                }
            }
        }
        else if (key_pressed == 2) // Key1: I2C 제어
        {
            Uart1_Printf("Using I2C Communication\n");
            if (Uart1_Rx_In)
            {
                received_command = Uart1_Rx_Data;
                Uart1_Rx_In = 0;
                
                if (received_command >= '1' && received_command <= '8')
                {
                    speed_level = (received_command - '0') * 10;
                    Uart1_Printf("Speed Level: %d\n", speed_level);
                }
                else
                {
                    device_execute(received_command, speed_level);
                    control_led_with_i2c(speed_level);
                }
                
            }
        }
    }
}