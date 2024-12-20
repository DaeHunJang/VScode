#include <device_driver.h>

#define TIM2_FREQUENCY 72000000 // 타이머 클럭 (72MHz)
#define MOTOR_PWM_FREQ 100000    // PWM 주파수 (10kHz)

void device_init()
{
    Uart1_Init(115200);
    Uart1_RX_Interrupt_Enable(1);
    Clock_Init();

    SCB->VTOR = 0x08003000;
    SCB->SHCSR = 0;

    RCC->APB1ENR |= (1 << 0);    // TIM2 클럭 활성화

    // TIM2 PWM 설정
    TIM2->PSC = (TIM2_FREQUENCY / MOTOR_PWM_FREQ) - 1; // 프리스케일러 설정
    TIM2->ARR = 100;                                   // 자동 리로드 값 (듀티 사이클 0~100%)
    TIM2->CCR3 = 0;                                    // 채널 3 (PA2) 듀티 사이클 초기화
    TIM2->CCR4 = 0;                                    // 채널 4 (PA3) 듀티 사이클 초기화
    TIM2->CCMR2 |= (0x6 << 4) | (0x6 << 12); // CH3, CH4: PWM 모드 1
    TIM2->CCER |= (1 << 8) | (1 << 12);
    TIM2->CR1 |= (1 << 0); // TIM2 활성화

    // PortA Clock ON
    Macro_Set_Bit(RCC->APB2ENR, 2);
    // PA1(EN),PA2(1A),PA3(2A) ->General Purpose Output Push-Pull
    Macro_Write_Block(GPIOA->CRL, 0xff, 0xBB, 8);

    //I2C init
    I2C_Init(5000);
	I2C_Config_GPIO(0xFF);
}

void device_execute(char command, int speed)
{    
    switch (command) {
    case 'S': // 정지`
        Motor_Stop();
        Uart1_Printf("Motor Stopped\n");
        break;
    case 'F': // 정방향 회전
        Motor_Forward(speed);
        Uart1_Printf("Motor Forward: Speed %d\n", speed);
        break;
    case 'R': // 역방향 회전
        Motor_Reserve(speed);
        Uart1_Printf("Motor Reverse: Speed %d\n", speed);
        break;
    default: // 유효하지 않은 명령
        Uart1_Printf("Invalid Command: %c\n", command);
        break;
    }
}

void Motor_Stop(void)
{
    TIM2->CCR3 = 0; // PA2 (CH3) Low
    TIM2->CCR4 = 0; // PA3 (CH4) Low
}

void Motor_Forward(int speed)
{
    TIM2->CCR3 = speed; // PA2 (CH3): 속도 설정
    TIM2->CCR4 = 0;     // PA3 (CH4): Low
    I2C_Write_GPIO()
}

void Motor_Reserve(int speed)
{
    TIM2->CCR3 = 0;     // PA2 (CH3): Low
    TIM2->CCR4 = speed; // PA3 (CH4): 속도 설정
}

