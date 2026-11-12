/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 10-06-2026
Language/ver     : C++ in VS Code

Description      : LAB_EXTI - Problem 1. Counter 0~9 on FND_0 every 1 sec, SW2 pause, SW1 reset (EXTI)
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define SW1_PIN    PD_2			//EVAL board JKIT SW1
#define SW2_PIN    PA_4			//EVAL board JKIT SW2

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};

volatile uint8_t num = 0;
volatile uint8_t paused = 0;

// Initialiization
void setup(void)
{
    MCU_init();                     // System Clock = 84MHz, SysTick 1msec

    // Initialize FND pins
    FND_init(pinFND);
    FND_select_init(selectFND);
    for (int i=0; i<8; i++){
        GPIO_pupd(pinFND[i], NO_PUPD);
        GPIO_otype(pinFND[i], PUSH_PULL);
        GPIO_ospeed(pinFND[i], MEDIUM);
    }
    GPIO_otype(selectFND[0], PUSH_PULL);
    FND_select(0);

    // Initialize GPIOD_2, GPIOA_4 for Input Button
    GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW1_PIN, EC_PU);  // PULL-UP for EVAL board
    GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW2_PIN, EC_PU);  // PULL-UP for EVAL board

    // Initialize EXTI PD_2, PA_4
    EXTI_init(SW1_PIN, FALL, 10);
    EXTI_init(SW2_PIN, FALL, 10);
}

// MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){
        FND_display(num);                          // display the number on FND_0
        delay_ms(1000);                            // wait 1 sec (SysTick)
        if (paused == 0) num = (num + 1) % 10;     // count up 0~9 when not paused
    }
}

// SW1 (PD_2): reset the number to 0
void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW1_PIN)) {
			num = 0;                           // reset
			FND_display(num);                  // display 0 right away
			clear_pending_EXTI(SW1_PIN);
	}
}

// SW2 (PA_4): pause or resume the counting
void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {
			paused ^= 1;                       // 1: paused, 0: counting
			clear_pending_EXTI(SW2_PIN);
	}
}
