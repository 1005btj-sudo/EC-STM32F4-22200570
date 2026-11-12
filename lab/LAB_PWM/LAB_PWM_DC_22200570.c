/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 11-02-2026
Modified         : 11-02-2026
Language/ver     : C in VS Code

Description      : LAB_PWM_DC - Smart mini-fan (DC motor) with FSM
                   B1 (PC_13) EXTI       : MODE  OFF(0%) -> MID(50%) -> HIGH(100%) -> OFF ...
                   IR sensor (PA_4) DIN  : object near -> PAUSE (B1 ignored), away -> RESUME previous MODE
                   PWM PA_0 (TIM2_CH1)   : 1 msec period (1 kHz), DIR PC_2 (Digital Out)
                   TIM3 update interrupt : 500 msec (LED blink 1 sec in PAUSE, USART print every 2 sec)
                   LED LD2 (PA_5)        : OFF -> off, MID/HIGH -> on, PAUSE -> blinking
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecUART2.h"

//==================================================================
// User GPIO Pin definitions
//==================================================================
#define BUTTON_PIN PC_13			// B1 Button (Pull-Up)
#define IR_PIN     PA_4				// IR Proximity Sensor (Pull-Up) : LOW = object detected
#define LED_PIN    PA_5				// Nucleo LD2
#define DIR_PIN    PC_2				// DC motor driver DIR
#define PWM_PIN    PA_0				// DC motor driver PWM (TIM2_CH1)

#define PWM_PERIOD_US   1000		// 1 msec = 1 kHz
#define DIR             0			// 0: duty = targetPWM

// Input X : Button B1 (0: not pressed, 1: pressed)
#define X_NONE   0
#define X_PRESS  1
// Input Y : IR sensor (0: object far -> RUN, 1: object near -> PAUSE)
#define Y_FAR    0
#define Y_NEAR   1

// MODE (state)
#define S_OFF   0
#define S_MID   1
#define S_HIGH  2

//==================================================================
// FSM : state = MODE, inputs X (B1) and Y (IR sensor), outputs duty and LED
//==================================================================
typedef struct {
	uint32_t next[2][2];			// [X][Y]  : next state
	float    duty[2];				// [Y]     : PWM duty  (Y_FAR : MODE speed,  Y_NEAR : 0)
	uint32_t led[2];				// [Y]     : LED (0: off, 1: on, 2: blink)
} State_t;

State_t FSM[3] = {
	//  next[X_NONE][Y_FAR,Y_NEAR]   next[X_PRESS][Y_FAR,Y_NEAR]     duty[Y_FAR,Y_NEAR]   led[Y_FAR,Y_NEAR]
	{ {{S_OFF,  S_OFF },            {S_MID,  S_OFF }},              {0.0f, 0.0f},        {0, 2} },	// S_OFF  : 0%
	{ {{S_MID,  S_MID },            {S_HIGH, S_MID }},              {0.5f, 0.0f},        {1, 2} },	// S_MID  : 50%
	{ {{S_HIGH, S_HIGH},            {S_OFF,  S_HIGH}},              {1.0f, 0.0f},        {1, 2} },	// S_HIGH : 100%
};

// Global Variables
// use   volatile uint32_t   instead of uint32_t if used in Interrupt ISR
volatile uint32_t state      = S_OFF;
volatile uint32_t btn_input  = X_NONE;		// set in EXTI ISR, cleared in main loop
volatile uint32_t tick_500ms = 0;			// counted in TIM3 ISR
uint32_t ir_input = Y_FAR;
float    duty     = 0.0f;

void setup(void);
void next_state(void);
void state_output(void);

//==================================================================
//  Main
//==================================================================
int main(void) {
	// Initialiization --------------------------------------------------------
	setup();
	printf("LAB_PWM_DC : Smart mini-fan\r\n");

	// Inifinite Loop ----------------------------------------------------------
	while(1){
		ir_input = (GPIO_read(IR_PIN) == LOW) ? Y_NEAR : Y_FAR;	// LOW: object detected

		if (btn_input == X_PRESS){				// change the MODE by the button input
			next_state();						// (stays when PAUSE)
			btn_input = X_NONE;
		}
		state_output();							// PWM duty and LED by (state, ir_input)

		if (tick_500ms >= 4){					// every 2 sec
			tick_500ms = 0;
			printf("MODE = %lu (0:OFF 1:MID 2:HIGH), duty = %.2f, PAUSE = %lu\r\n", state, duty, ir_input);
		}
	}
}

//==================================================================
//  Setup
//==================================================================
void setup(void){
	RCC_PLL_init();								// System Clock = 84MHz
	USART2_init();								// USART2 (Tera Term), 9600 baud

	// Button B1 (PC_13) : Digital In, Pull-Up, EXTI falling edge
	GPIO_init(BUTTON_PIN, EC_DIN);
	GPIO_pupd(BUTTON_PIN, EC_PU);
	EXTI_init(BUTTON_PIN, FALL, 0);				// EXTI priority 0 (TIM3 priority 2 in TIM_UI_init)

	// IR Proximity Sensor (PA_4) : Digital In, Pull-Up
	GPIO_init(IR_PIN, EC_DIN);
	GPIO_pupd(IR_PIN, EC_PU);

	// LED LD2 (PA_5) : Digital Out
	GPIO_init(LED_PIN, OUTPUT);
	GPIO_write(LED_PIN, LOW);

	// DIR (PC_2) : Digital Out, Push-Pull
	GPIO_init(DIR_PIN, OUTPUT);
	GPIO_otype(DIR_PIN, PUSH_PULL);
	GPIO_write(DIR_PIN, DIR);

	// PWM (PA_0, TIM2_CH1) : 1 msec period (1 kHz), start at 0%
	PWM_init_us(PWM_PIN, PWM_PERIOD_US);
	PWM_duty(PWM_PIN, 0.0f);

	// TIM3 Update-Event Interrupt every 500 msec
	TIM_UI_init(TIM3, 500);
}

// next state by the button (X) and the sensor (Y)
void next_state(void){
	state = FSM[state].next[btn_input][ir_input];
}

// output of the state : PWM duty (with DIR) and LED
void state_output(void){
	float targetPWM = FSM[state].duty[ir_input];
	duty = fabs(DIR - targetPWM);				// duty with consideration of DIR = 1 or 0
	PWM_duty(PWM_PIN, duty);

	uint32_t led = FSM[state].led[ir_input];
	if (led == 0)		GPIO_write(LED_PIN, LOW);
	else if (led == 1)	GPIO_write(LED_PIN, HIGH);
	// led == 2 (blink) : toggled in TIM3_IRQHandler every 500 msec
}

//==================================================================
//  Interrupt Service Routines
//==================================================================

// B1 (PC_13) : MODE change request
void EXTI15_10_IRQHandler(void){
	if (is_pending_EXTI(BUTTON_PIN)){
		btn_input = X_PRESS;
		clear_pending_EXTI(BUTTON_PIN);
	}
}

// TIM3 Update Interrupt Handler : every 500 msec
void TIM3_IRQHandler(void){
	if(is_UIF(TIM3)){							// Check UIF(update interrupt flag)
		tick_500ms++;
		if (FSM[state].led[ir_input] == 2)		// PAUSE : LED blinking (period 1 sec)
			led_toggle(LED_PIN);
		clear_UIF(TIM3);						// Clear TIM_UI flag
	}
}
