/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 11-05-2026
Modified         : 11-10-2026
Language/ver     : C in VS Code

Description      : LAB_TIMER_ICAP - Ultrasonic Distance Sensor (HC-SR04) with Input Capture
                   TRIG : PA_6 (TIM3_CH1) PWM, 50 msec period, 10 usec pulse
                   ECHO : PB_6 (TIM4_CH1) ICAP, IC1 = rising edge, IC2 = falling edge, tick 10 usec
                   distance [cm] = echo pulse width [usec] / 58
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"
#include "ecICAP2.h"
#include "ecPWM2.h"
#include "ecUART2.h"

#define LED_PIN		PA_5		// Nucleo LD2
#define TRIG		PA_6		// TIM3_CH1 : trigger output
#define ECHO		PB_6		// TIM4_CH1 : echo capture input

uint32_t pwm_period_ms=50;		// trigger period
uint32_t pulse_width_us=10;		// trigger pulse width
uint32_t uTick=10;				// counter tick [usec]
uint32_t timer_arr  = 65536;	// ticks per counter wrap (ARR+1)

volatile uint32_t ovf_cnt = 0;		//counts overflows
volatile uint32_t cap_prev   = 0;	// CCR of the rising edge
volatile uint32_t cap_curr    = 0;	// CCR of the falling edge
volatile uint32_t counts = 0;		// [pulses]
volatile float timeInterval = 0;	// [usec]
float distance = 0;					// [cm]

void setup(void){
	RCC_PLL_init();
	SysTick_init();
	GPIO_init(LED_PIN,OUTPUT);
	USART2_init();

	// PWM: Trigger signal of 50 msec period, 10 usec pulse
	PWM_init(TRIG, pwm_period_ms);
	PWM_pulsewidth_us(TRIG, pulse_width_us);
	GPIO_otype(TRIG, PUSH_PULL);			// AF, Push-Pull, No Pull-up Pull-down, Fast
	GPIO_pupd(TRIG, NO_PUPD);
	GPIO_ospeed(TRIG, FAST);

	// Input capture  rising edge TIn=ICn, tick = uTick usec
	ICAP_init(ECHO, IC_RISE);
	ICAP_ICn_init(ECHO, IC_FALL, IC_2);		//TI1 -> IC2, falling
	ICAP_tick(ECHO, uTick);

	timer_arr=TIM4->ARR + 1;
}

int main(void){
	setup();
	printf("LAB_TIMER_ICAP : HC-SR04  TRIG PA_6, ECHO PB_6\r\n");

	while(1){
		distance = (float)timeInterval / 58.0f;		// [usec] -> [cm]
		printf("echo = %.0f usec, distance = %.1f cm\r\n", timeInterval, distance);
		led_toggle(LED_PIN);
		delay_ms(500);
	}
}

void TIM4_IRQHandler(void){
	// Counter overflow
	if(is_UIF(TIM4)){
		ovf_cnt++;
		clear_UIF(TIM4);
	}

	// Rising edge captured on IC1
	if(is_CCIF(TIM4, IC_1)){					// IC1 : rising edge, SAME pin (TI1)
		cap_prev = ICAP_read(ECHO, IC_1);
		clear_CCIF(TIM4,IC_1);
	}
	// Falling edge captured on IC2
	if(is_CCIF(TIM4, IC_2)){					// IC2 : falling edge, SAME pin (TI1)
		cap_curr = ICAP_read(ECHO, IC_2);

		// Ticks between the two edges, then scaled to usec.
		counts = (cap_curr-cap_prev) + (ovf_cnt*timer_arr);
		timeInterval=counts*uTick;

		ovf_cnt    = 0;
		clear_CCIF(TIM4, IC_2);
	}
}
