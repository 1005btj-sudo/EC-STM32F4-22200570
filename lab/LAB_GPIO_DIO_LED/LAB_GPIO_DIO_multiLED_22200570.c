/**
******************************************************************************
* @author	Lee Jae Yong (22200570)
* @Mod		2026-09-20
* @brief	Embedded Controller:  LAB Digital In/Out
*					 - Toggle multiple LEDs by Button B1 pressing
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"

PinName_t LED_pin[4] = {PB_12, PB_13, PB_14, PB_15};
PinName_t button_pin = PA_4;

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	
	int ledIdx = 0;
	int buttonState = 1;
	int prevState = 1;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		buttonState = GPIO_read(button_pin);
		if (prevState == 1 && buttonState == 0){			// falling edge
			delay_ms_HSI(20);								// debouncing
			if (GPIO_read(button_pin) == 0)	ledIdx = (ledIdx + 1) % 4;
		}
		prevState = buttonState;
		
		for (int i = 0; i < 4; i++){
			if (i == ledIdx)	GPIO_write(LED_pin[i], HIGH);
			else				GPIO_write(LED_pin[i], LOW);
		}
	}
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();

	// Configuration button pin
	GPIO_init(button_pin, INPUT);  // calls RCC_GPIOA_enable()
	GPIO_pupd(button_pin, PULL_UP);

	// Configuration LED pins
	for (int i = 0; i < 4; i++){
		GPIO_init(LED_pin[i], OUTPUT);    // calls RCC_GPIOB_enable()
		GPIO_pupd(LED_pin[i], PULL_UP);
		GPIO_otype(LED_pin[i], OPEN_DRAIN);
		GPIO_ospeed(LED_pin[i], MEDIUM);
	}
}
