/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 11-02-2026
Modified         : 11-02-2026
Language/ver     : C in VS Code

Description      : LAB_PWM_RC - RC Servo Motor (SG90) control with PWM
                   PA_1 (TIM2_CH2) : PWM 20 msec period, pulse 0.5 ~ 2.5 msec
                   TIM3 update interrupt (500 msec) : angle 0 -> 180 -> 0 deg, step 10 deg
                   B1 (PC_13) EXTI : reset to 0 deg and start over
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"

#define BUTTON_PIN PC_13			// B1 Button (Pull-Up)
#define PWM_PIN    PA_1				// TIM2_CH2

#define PWM_PERIOD_MS   20			// 20 msec = 50 Hz
#define PULSE_MIN_US    500			// 0.5 msec  ->   0 deg
#define PULSE_MAX_US    2500		// 2.5 msec  -> 180 deg
#define ANGLE_MAX       180
#define ANGLE_STEP      10

// use   volatile uint32_t   instead of uint32_t if used in Interrupt ISR
volatile int32_t angle = 0;			// 0 ~ 180 [deg]
volatile int32_t dir   = 1;			// +1: increasing, -1: decreasing

void setup(void);
void servo_angle(int32_t deg);

int main(void) {
	// Initialiization --------------------------------------------------------
	setup();

	// Inifinite Loop ----------------------------------------------------------
	while(1){}
}

// Initialiization
void setup(void){
	RCC_PLL_init();								// System Clock = 84MHz

	// Button B1 (PC_13) : Digital In, Pull-Up, EXTI falling edge
	GPIO_init(BUTTON_PIN, EC_DIN);
	GPIO_pupd(BUTTON_PIN, EC_PU);
	EXTI_init(BUTTON_PIN, FALL, 0);				// EXTI priority 0 (TIM3 priority 2 in TIM_UI_init)

	// PWM (PA_1, TIM2_CH2) : 20 msec period
	PWM_init(PWM_PIN, PWM_PERIOD_MS);
	servo_angle(angle);							// start at 0 deg (pulse 0.5 msec)

	// TIM3 Update-Event Interrupt every 500 msec
	TIM_UI_init(TIM3, 500);
}

// angle [deg] -> pulse width [usec] : 0 deg = 0.5 msec, 180 deg = 2.5 msec
void servo_angle(int32_t deg){
	uint32_t pulse_us = PULSE_MIN_US + (PULSE_MAX_US - PULSE_MIN_US) * deg / ANGLE_MAX;
	PWM_pulsewidth_us(PWM_PIN, pulse_us);
}

// TIM3 Update Interrupt Handler : every 500 msec
void TIM3_IRQHandler(void){
	if(is_UIF(TIM3)){							// Check UIF(update interrupt flag)
		angle += dir * ANGLE_STEP;				// 10 deg step
		if (angle >= ANGLE_MAX){				// 180 deg -> turn back
			angle = ANGLE_MAX;
			dir = -1;
		}
		else if (angle <= 0){					// 0 deg -> turn back
			angle = 0;
			dir = 1;
		}
		servo_angle(angle);
		clear_UIF(TIM3);						// Clear TIM_UI flag
	}
}

// B1 (PC_13) : reset to 0 deg and start over
void EXTI15_10_IRQHandler(void){
	if (is_pending_EXTI(BUTTON_PIN)){
		angle = 0;
		dir = 1;
		servo_angle(angle);
		clear_pending_EXTI(BUTTON_PIN);
	}
}
