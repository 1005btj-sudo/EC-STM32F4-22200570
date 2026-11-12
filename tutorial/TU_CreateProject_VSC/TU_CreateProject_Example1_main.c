/*
 * Embedded Controller - Tutorial: Create Project (VS Code / PlatformIO)
 * Example 1 : Register-level LED ON
 * Board      : NUCLEO-F411RE   (LED2 = PA5, User button = PC13)
 * env        : TU_CreateProject_Example1
 */

#include "stm32f4xx.h"

#define LED_PIN    5
#define BUTTON_PIN 13

int main(void) {
	/* Part 1. RCC Register Setting */
	RCC->CR |= ((uint32_t)RCC_CR_HSION);					// Enable HSI
	while ((RCC->CR & (uint32_t)RCC_CR_HSIRDY) == 0) {;}	// Wait until HSI is ready
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));		// Clear SW bits
	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;					// Select HSI as system clock
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != 0) {;}	// Wait until HSI is the system clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;					// Enable GPIOA clock

	/* Part 2. GPIO Register Setting */
	GPIOA->MODER &= ~(3UL << (2 * LED_PIN));				// Clear mode bits
	GPIOA->MODER |=  (1UL << (2 * LED_PIN));				// Output mode

	while (1) {
		GPIOA->ODR |= (1UL << LED_PIN);						// LED ON
	}
}
