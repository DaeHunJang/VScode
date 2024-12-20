#include "device_driver.h"

char received_command;
int speed_level = 50; // 기본 속도 (%)
extern volatile int Uart1_Rx_In;
extern volatile int Uart1_Rx_Data;

void Main(void)
{
    device_init();
	Uart1_Printf("Motor Control System Ready\n");

    for(;;) {
        // UART로부터 명령 수신
        if (Uart1_Rx_In) { 
            received_command = Uart1_Rx_Data;  
            if (received_command >= '1' && received_command <= '9') {
                // 속도 설정 (1~9 → 10%~90%)
                speed_level = (received_command - '0') * 10;
                Uart1_Printf("Speed Level: %d\n", speed_level);
            } else {
                // 명령에 따라 모터 제어
                device_execute(received_command, speed_level);
            }
            Uart1_Rx_In = 0;
        }
    }
}
