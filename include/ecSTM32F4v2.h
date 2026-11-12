//ecSTM32F4v2.h

/**
******************************************************************************
* @course   Embedded Controller- HGU
* @author	iiLAB
* @mod		2024-8-05 by YKKIM
* @mod		2026-09-30 by Lee Jae Yong (22200570) - ecEXTI2, ecSysTick2 added; MCU_init() added
* @mod		2026-11-05 by Lee Jae Yong (22200570) - ecTIM2, ecPWM2, ecICAP2 added (Tutorial: Timer Input Capture)
* @mod		2026-10-19 by Lee Jae Yong (22200570) - ecUART2, ecStepper2 added
* @brief	STM32F411 Library for EC
*
******************************************************************************
*/

#ifndef __EC_STM_H
#define __EC_STM_H

// STM built-In Library
#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "math.h"

// EC course Library
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecICAP2.h"
#include "ecStepper2.h"
#include "ecUART2.h"


// Custom MCU initialization
void MCU_init(void){
    // CLOCK PLL 84MHz
    RCC_PLL_init();
    
    // SysTick 1msec
    SysTick_init();    
    
    // Button PC13
    GPIO_init(PC_13, INPUT);
    GPIO_pupd(PC_13, EC_PD);    
    
    // LED PA5
    GPIO_init(PA_5, OUTPUT);    

    // EXTILine_init(PC_13, FALLING); // EXTI PC13 
    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...        
    // USART Default Initialization
    // ...
    // Others
}

#endif
