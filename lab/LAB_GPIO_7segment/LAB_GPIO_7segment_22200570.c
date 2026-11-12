/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 09-17-2026
Modified         : 09-21-2026
Language/ver     : C++ in VS Code

Description      : LAB_GPIO_7segment - Problem 2. Counter 0~9 on FND_0 by SW2
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
// PinName_t selectFND[4]={PA_10, ... }
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};

#define BUTTON_PIN PA_4

void setup(void){
    // Intialize System Clock
    RCC_HSI_init();
    
    // Intialize FND pins and Others
    FND_init(pinFND);
    FND_select_init(selectFND);
    for (int i=0; i<8; i++){
        GPIO_pupd(pinFND[i], NO_PUPD);
        GPIO_otype(pinFND[i], PUSH_PULL);
        GPIO_ospeed(pinFND[i], MEDIUM);
    }
    for (int i=0; i<4; i++){
        GPIO_otype(selectFND[i], PUSH_PULL);
    }
    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_UP);
};

int main(void) {
    setup();
    uint8_t num = 0;
    int buttonState = 1;
    int prevState = 1;

    while (1) {
        FND_select(0);
        FND_display(num);

        buttonState = GPIO_read(BUTTON_PIN);
        if (prevState == 1 && buttonState == 0){		// falling edge
            delay_ms_HSI(20);							// debouncing
            if (GPIO_read(BUTTON_PIN) == 0)	num = (num + 1) % 10;
        }
        prevState = buttonState;
    }
}
