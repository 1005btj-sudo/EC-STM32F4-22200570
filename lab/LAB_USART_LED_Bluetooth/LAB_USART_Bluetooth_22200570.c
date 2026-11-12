/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 10-19-2026
Modified         : 10-26-2026
Language/ver     : C++ in VS Code

Description      : LAB_USART_Bluetooth - Problem 2. Control Stepper Motor via Bluetooth
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"  // this should include #include "ecUART2.h", "ecStepper2.h"

static volatile uint8_t BT_Data = 0;

// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PB_10,PB_4,PB_5,PB_3};

void setup(void){
	RCC_PLL_init();
	SysTick_init();

	// USART1: BT serial init
	USART1_init();
	USART1_baud(BAUD_9600);

	// LD2
	GPIO_init(PA_5, OUTPUT);

	stepper_init(FULL, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(10);                          	//  set stepper motor speed
}

int main(void){
	setup();
	uint32_t rev=2;
	uint32_t steps=STEP_PER_REV*rev;

	while(1){
		if (BT_Data == 'J'){
			BT_Data = 0;
			stepper_step(steps, DIR_CW);		// 'J' : CW 2 rev
		}
		else if (BT_Data == 'K'){
			BT_Data = 0;
			stepper_step(steps, DIR_CCW);		// 'K' : CCW 2 rev
		}
	}
}

void USART1_IRQHandler(){          	// USART1 RX Interrupt
	if(is_USART1_RXNE()){
		BT_Data = USART1_read();				// RX from BT
		USART1_write(&BT_Data,1);				// TX to BT (PC) Echo of keyboard typing
		if (BT_Data == 'L')			GPIO_write(PA_5, LOW);		// 'L' : LD2 OFF
		else if (BT_Data == 'H')	GPIO_write(PA_5, HIGH);		// 'H' : LD2 ON
		else if (BT_Data == 'P')	stepper_stop();				// 'P' : Emergency STOP
	}
}

