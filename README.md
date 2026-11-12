# Embedded Controller - STM32F411 Driver Library

Written by: Lee Jae Yong (22200570)

Program: C/C++

IDE/Compiler: VS Code, PlatformIO

OS: Windows 11

MCU: STM32F411RE, Nucleo-64

---

**Table of Contents**

* [PinName Configuration](#pinname-configuration)
  * [Header File](#header-file)
  * [ecPinmap()](#ecpinmap)
* [RCC](#rcc)
  * [Header File](#header-file-1)
  * [RCC_HSI_init()](#rcc_hsi_init)
  * [RCC_PLL_init()](#rcc_pll_init)
  * [delay_ms_HSI()](#delay_ms_hsi)
  * [RCC_GPIOA_enable()](#rcc_gpioa_enable)
  * [RCC_GPIOB_enable()](#rcc_gpiob_enable)
  * [RCC_GPIOC_enable()](#rcc_gpioc_enable)
  * [RCC_GPIOD_enable()](#rcc_gpiod_enable)
  * [RCC_GPIOE_enable()](#rcc_gpioe_enable)
  * [RCC_GPIOH_enable()](#rcc_gpioh_enable)
* [GPIO Digital InOut](#gpio-digital-inout)
  * [Header File](#header-file-2)
  * [GPIO_init()](#gpio_init)
  * [GPIO_mode()](#gpio_mode)
  * [GPIO_ospeed()](#gpio_ospeed)
  * [GPIO_otype()](#gpio_otype)
  * [GPIO_pupd()](#gpio_pupd)
  * [GPIO_write()](#gpio_write)
  * [GPIO_read()](#gpio_read)
  * [FND_init()](#fnd_init)
  * [FND_select_init()](#fnd_select_init)
  * [FND_display()](#fnd_display)
  * [FND_select()](#fnd_select)
  * [pinMode()](#pinmode)
  * [digitalWrite()](#digitalwrite)
  * [digitalRead()](#digitalread)
  * [led_toggle()](#led_toggle)
* [SysTick](#systick)
  * [Header File](#header-file-3)
  * [SysTick_init()](#systick_init)
  * [SysTick_Handler()](#systick_handler)
  * [SysTick_counter()](#systick_counter)
  * [delay_ms()](#delay_ms)
  * [SysTick_reset()](#systick_reset)
  * [SysTick_val()](#systick_val)
* [EXTI](#exti)
  * [Header File](#header-file-4)
  * [EXTI_init()](#exti_init)
  * [EXTI_enable()](#exti_enable)
  * [EXTI_disable()](#exti_disable)
  * [is_pending_EXTI()](#is_pending_exti)
  * [clear_pending_EXTI()](#clear_pending_exti)
* [Stepper Motor](#stepper-motor)
  * [Header File](#header-file-5)
  * [stepper_init()](#stepper_init)
  * [stepper_speed()](#stepper_speed)
  * [stepper_step()](#stepper_step)
  * [stepper_out()](#stepper_out)
  * [stepper_stop()](#stepper_stop)
* [USART](#usart)
  * [Header File](#header-file-6)
  * [USART_init()](#usart_init)
  * [USART_baud()](#usart_baud)
  * [USART_pins()](#usart_pins)
  * [USART1_baud()](#usart1_baud)
  * [USART2_baud()](#usart2_baud)
  * [USART1_init()](#usart1_init)
  * [USART2_init()](#usart2_init)
  * [USART1_write()](#usart1_write)
  * [USART2_write()](#usart2_write)
  * [USART1_read()](#usart1_read)
  * [USART2_read()](#usart2_read)
  * [is_USART1_RXNE()](#is_usart1_rxne)
  * [is_USART2_RXNE()](#is_usart2_rxne)
  * [USART_clock_enable()](#usart_clock_enable)
  * [USART_write()](#usart_write)
  * [USART_read()](#usart_read)
  * [is_USART_RXNE()](#is_usart_rxne)
  * [USART_delay()](#usart_delay)
* [Timer](#timer)
  * [Header File](#header-file-7)
  * [TIM_UI_init()](#tim_ui_init)
  * [TIM_UI_init_us()](#tim_ui_init_us)
  * [TIM_UI_enable()](#tim_ui_enable)
  * [TIM_UI_disable()](#tim_ui_disable)
  * [is_UIF()](#is_uif)
  * [clear_UIF()](#clear_uif)
  * [TIM_init()](#tim_init)
  * [TIM_init_us()](#tim_init_us)
  * [TIM_period()](#tim_period)
  * [TIM_period_ms()](#tim_period_ms)
  * [TIM_period_us()](#tim_period_us)
  * [get_TIM_IRQn()](#get_tim_irqn)
  * [TIM_clock_enable()](#tim_clock_enable)
* [PWM](#pwm)
  * [Header File](#header-file-8)
  * [PWM_init()](#pwm_init)
  * [PWM_init_us()](#pwm_init_us)
  * [PWM_init_config()](#pwm_init_config)
  * [PWM_duty()](#pwm_duty)
  * [PWM_pulsewidth()](#pwm_pulsewidth)
  * [PWM_pulsewidth_us()](#pwm_pulsewidth_us)
  * [PWM_mode_config()](#pwm_mode_config)
  * [PWM_pinmap()](#pwm_pinmap)
* [Input Capture](#input-capture)
  * [Header File](#header-file-9)
  * [ICAP_init()](#icap_init)
  * [ICAP_ICn_init()](#icap_icn_init)
  * [ICAP_tick()](#icap_tick)
  * [ICAP_read()](#icap_read)
  * [is_CCIF()](#is_ccif)
  * [clear_CCIF()](#clear_ccif)
  * [ICAP_pinmap()](#icap_pinmap)
  * [ICAP_filter()](#icap_filter)
  * [ICAP_ICn_select()](#icap_icn_select)
* [Custom Initialization](#custom-initialization)
  * [Header File](#header-file-10)
  * [MCU_init()](#mcu_init)

---

## PinName Configuration

### Header File

`#include "ecPinNames.h"`

```c
#ifndef EC_PINNAMES_H
#define EC_PINNAMES_H

#include "stm32f411xe.h"

#ifdef __cplusplus
extern "C" {
#endif


// Bitwise Macro Definition
#define BIT_SET(REG, BIT)      	((REG) |= 1<< (BIT))
#define BIT_CLEAR(REG, BIT)     ((REG) &= ~1<<(BIT))
#define BIT_READ(REG, BIT)      ((REG)>>BIT & (1))
#define BITS_SET(REG, BIT,NUM)     ((REG) |= NUM<< (BIT))
#define BITS_CLEAR(REG, BIT,NUM)   ((REG) &= ~(NUM<< (BIT))
//#define BITS_CLEAR(REG, BIT,NUM)   ((REG) &= ~((0x1<< NUM)-1)<<(BIT))


// Pinname Config
typedef enum {
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,
    PortE = 4,
    PortF = 5,
    PortG = 6,
    PortH = 7,
    PortI = 8,
    PortJ = 9,
    PortK = 10
} PortName_t;



typedef enum {
    PA_0  = 0x00,
    PA_1  = 0x01,    
    PA_2  = 0x02,
    PA_3  = 0x03,
    PA_4  = 0x04,    
    PA_5  = 0x05,
    PA_6  = 0x06,
    PA_7  = 0x07,
    PA_8  = 0x08,
    PA_9  = 0x09,
    PA_10 = 0x0A,
    PA_11 = 0x0B,
    PA_12 = 0x0C,
    PA_13 = 0x0D,
    PA_14 = 0x0E,
    PA_15 = 0x0F,
    
    PB_0  = 0x10,
    PB_1  = 0x11,
    PB_2  = 0x12,
    PB_3  = 0x13,
    PB_4  = 0x14,
    PB_5  = 0x15,
    PB_6  = 0x16,
    PB_7  = 0x17,
    PB_8  = 0x18,
    PB_9  = 0x19,
    PB_10 = 0x1A,
    PB_11 = 0x1B,
    PB_12 = 0x1C,
    PB_13 = 0x1D,
    PB_14 = 0x1E,
    PB_15 = 0x1F,

    PC_0  = 0x20,
    PC_1  = 0x21,
    PC_2  = 0x22,
    PC_3  = 0x23,
    PC_4  = 0x24,
    PC_5  = 0x25,
    PC_6  = 0x26,
    PC_7  = 0x27,
    PC_8  = 0x28,
    PC_9  = 0x29,
    PC_10 = 0x2A,
    PC_11 = 0x2B,
    PC_12 = 0x2C,
    PC_13 = 0x2D,
    PC_14 = 0x2E,
    PC_15 = 0x2F,

    PD_2  = 0x32,

    PH_0  = 0x70,
    PH_1  = 0x71,


    // Arduino connector namings
    A0          = PA_0,
    A1          = PA_1,
    A2          = PA_4,
    A3          = PB_0,
    A4          = PC_1,
    A5          = PC_0,
    D0          = PA_3,
    D1          = PA_2,
    D2          = PA_10,
    D3          = PB_3,
    D4          = PB_5,
    D5          = PB_4,
    D6          = PB_10,
    D7          = PA_8,
    D8          = PA_9,
    D9          = PC_7,
    D10         = PB_6,
    D11         = PA_7,
    D12         = PA_6,
    D13         = PA_5,
    D14         = PB_9,
    D15         = PB_8,


    // Not connected
    NC = (int)0xFFFFFFFF
} PinName_t;


void ecPinmap(PinName_t pinName, GPIO_TypeDef **GPIOx, unsigned int *pin);




#ifdef __cplusplus
}
#endif

#endif
```

### ecPinmap()

Separates the port and the pin number from the pin name.

```c
void ecPinmap(PinName_t pinName, GPIO_TypeDef **GPIOx, unsigned int *pin)
{
	
	unsigned int pinNum= pinName & (0x000F);
	*pin=pinNum;

	unsigned int portNum=(pinName>>4);
	
	
	if (portNum==0)
		*GPIOx=GPIOA;
	else if (portNum==1)
		*GPIOx=GPIOB;
	else if (portNum==2)
		*GPIOx=GPIOC;
	else if (portNum==3)
		*GPIOx=GPIOD;
	else if (portNum==7)
		*GPIOx=GPIOH;
	else 
		*GPIOx=GPIOA;
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **GPIOx**: the port of the pin (output)
* **pin**: the pin number, 0 to 15 (output)

**Example code**

```c
ecPinmap(pinName, &Port, &pin);
```

---

## RCC

### Header File

`#include "ecRCC2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 09-30-2026
Language/ver     : C++ in VS Code

Description      : System Clock Library. Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/


#ifndef __EC_RCC2_H
#define __EC_RCC2_H


#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecPinNames.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


extern volatile int EC_SYSCLK;		// current SYSCLK [Hz], set by RCC_HSI_init()/RCC_PLL_init()
void delay_ms_HSI(uint32_t ms); 
void RCC_HSE_init(void); 
void RCC_PLL_init(void);
void RCC_GPIOA_enable(void);
void RCC_GPIOB_enable(void);
void RCC_GPIOC_enable(void);
void RCC_GPIOD_enable(void);


/*---------------------------------------------------------------- 
                    [EXERCISE]
---------------------------------------------------------------- */

void RCC_GPIOE_enable(void);
void RCC_GPIOH_enable(void);

/*---------------------------------------------------------------- 
                    [Advanced EXERCISE]
---------------------------------------------------------------- */
// void RCC_GPIO_enable(GPIO_TypeDef * GPIOx);
void RCC_HSI_init(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_RCC2_H
```

### RCC_HSI_init()

Selects HSI as the system clock.

```c
void RCC_HSI_init() {
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= ((uint32_t)RCC_CR_HSION);
   	// RCC->CR |= (0x1UL << 0U);

	// Wait until HSI is ready
  	while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	// while ( (RCC->CR & (0x1UL << 1U) ) == 0 ) {;}
	
  // Select HSI as system clock source 
  	RCC->CFGR &= (uint32_t)(~RCC_CFGR_SW); 								// not essential
  	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI; 							//00: HSI16 oscillator used as system clock

	// Wait till HSI is used as system clock source
  	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != 0 ) {;}  
	//while ((RCC->CFGR & (0x3UL<< 2U) )!= 0 ) {;}  
	//while (((RCC->CFGR >>2U) & (0x3UL) )!= 0 ) {;}  

	EC_SYSCLK=16000000;	
}
```

**Parameters**

* None

**Example code**

```c
RCC_HSI_init();
```

### RCC_PLL_init()

Selects PLL as the system clock.

```c
void RCC_PLL_init() {	
	// To correctly read data from FLASH memory, the number of wait states (LATENCY)
  	// must be correctly programmed according to the frequency of the CPU clock
  	// (HCLK) and the supply voltage of the device.		
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |=  FLASH_ACR_LATENCY_2WS;
		
	// Enable the Internal High Speed oscillator (HSI)
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Disable PLL for configuration
	RCC->CR    &= ~RCC_CR_PLLON;
	
	// Select clock source to PLL
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC; 		// Set source for PLL: clear bits
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI; // Set source for PLL: 0 =HSI, 1 = HSE
	
	// Make PLL as 84 MHz
	// f(VCO clock) = f(PLL clock input) * (PLLN / PLLM) = 16MHz * 84/8 = 168 MHz
	// f(PLL_R) = f(VCO clock) / PLLP = 168MHz/2 = 84MHz
	RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLN) | 84U << 6;
	RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLM) | 8U ; 
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;  // 00: PLLP = 2, 01: PLLP = 4, 10: PLLP = 6, 11: PLLP = 8	
	
	
	// Enable PLL after configuration
	RCC->CR   |= RCC_CR_PLLON; 
	while((RCC->CR & RCC_CR_PLLRDY)>>25 != 0);
	
	// Select PLL as system clock
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	
	// Wait until System Clock has been selected
	while ((RCC->CFGR & RCC_CFGR_SWS) != 8UL);
	
	// The maximum frequency of the AHB and APB2 is 100MHz,
	// The maximum frequency of the APB1 is 50 MHz.
	RCC->CFGR &= ~RCC_CFGR_HPRE;  		// AHB prescaler = 1; SYSCLK not divided (84MHz)
	RCC->CFGR &= ~RCC_CFGR_PPRE1; 		// APB high-speed prescaler (APB1) = 2, HCLK divided by 2 (42MHz)
	RCC->CFGR |=  RCC_CFGR_PPRE1_2;
	RCC->CFGR &= ~RCC_CFGR_PPRE2; 		// APB high-speed prescaler (APB2) = 1, HCLK not divided	(84MHz)
	
	EC_SYSCLK=84000000;
}
```

**Parameters**

* None

**Example code**

```c
RCC_PLL_init();                                 // System Clock = 84MHz
```

### delay_ms_HSI()

Delays in milliseconds.

```c
void delay_ms_HSI(uint32_t ms) {
	//uint32_t EC_SYSCLK=16000000;
	volatile uint32_t cnt = ((uint32_t)EC_SYSCLK / (1000UL * 6)) * ms;
	while (cnt > 0) cnt--;
}
```

**Parameters**

* **ms**: delay time in milliseconds

**Example code**

```c
delay_ms_HSI(100);             					// delay 100 ms
```

### RCC_GPIOA_enable()

Enables the GPIO port clock.

```c
void RCC_GPIOA_enable()
{
	// RCC Peripheral Clock Enable Register 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}
```

**Parameters**

* None

**Example code**

```c
if (Port == GPIOA)
	RCC_GPIOA_enable();
```

### RCC_GPIOB_enable()

Enables the GPIO port clock.

```c
void RCC_GPIOB_enable()
{
	// RCC Peripheral Clock Enable Register 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
}
```

**Parameters**

* None

**Example code**

```c
if (Port == GPIOB)
	RCC_GPIOB_enable();
```

### RCC_GPIOC_enable()

Enables the GPIO port clock.

```c
void RCC_GPIOC_enable()
{
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}
```

**Parameters**

* None

**Example code**

```c
if (Port == GPIOC)
	RCC_GPIOC_enable();
```

### RCC_GPIOD_enable()

Enables the GPIO port clock.

```c
void RCC_GPIOD_enable()
{
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}
```

**Parameters**

* None

**Example code**

```c
if (Port == GPIOD)
	RCC_GPIOD_enable();
```

### RCC_GPIOE_enable()

Enables the GPIO port clock.

```c
void RCC_GPIOE_enable(void)
{
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
}
```

**Parameters**

* None

**Example code**

```c
if (Port == GPIOE)
	RCC_GPIOE_enable();
```

### RCC_GPIOH_enable()

Enables the GPIO port clock.

```c
void RCC_GPIOH_enable(void)
{
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
}
```

**Parameters**

* None

**Example code**

```c
if (Port == GPIOH)
	RCC_GPIOH_enable();
```

---

## GPIO Digital InOut

### Header File

`#include "ecGPIO2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 10-15-2026
Language/ver     : C++ in VS Code

Description      : GPIO Library. Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"

#define INPUT  0x00
#define OUTPUT 0x01
#define AF     0x02
#define ANALOG 0x03

#define HIGH 1
#define LOW  0

/*----------------------------------------------------------------
                    [EXERCISE]
---------------------------------------------------------------- */
#define NO_PUPD     0x00
#define PULL_UP     0x01
#define PULL_DOWN   0x02

#define PUSH_PULL   0x00
#define OPEN_DRAIN  0x01

#define LOW_SPEED   0x00
#define MEDIUM      0x01
#define FAST        0x02
#define HIGH_SPEED  0x03

#define PU          PULL_UP
#define PD          PULL_DOWN
#define EC_PU       PULL_UP
#define EC_PD       PULL_DOWN
#define EC_DIN      INPUT


#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void GPIO_init(PinName_t pinName, uint32_t mode);
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
void GPIO_otype(PinName_t pinName, uint32_t type);
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
void GPIO_write(PinName_t pinName, uint32_t Output);
uint32_t  GPIO_read(PinName_t pinName);
void led_toggle(PinName_t pinName);


// FND for JKIT board
extern int numberFND[12][8];
void FND_init(PinName_t *pinFND);
void FND_select_init(PinName_t *selectFND);
void FND_display(uint8_t num);
void FND_select(uint8_t digit);

// ARDUINO Syntax  (Optional)
void pinMode(PinName_t pin, uint32_t mode);
void digitalWrite(PinName_t pin, uint32_t value);
uint32_t  digitalRead(PinName_t pin);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
```

### GPIO_init()

Enables the port clock and sets the pin mode.

```c
void GPIO_init(PinName_t pinName, uint32_t mode){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	
	// Make it for GPIOC, GPIOD..GPIOH
	if (Port == GPIOC)
		RCC_GPIOC_enable();
	if (Port == GPIOD)
		RCC_GPIOD_enable();
	if (Port == GPIOE)
		RCC_GPIOE_enable();
	if (Port == GPIOH)
		RCC_GPIOH_enable();

	GPIO_mode(pinName, mode);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **mode**: INPUT(0), OUTPUT(1), AF(2), ANALOG(3)

**Example code**

```c
GPIO_init(BUTTON_PIN, INPUT);  
```

### GPIO_mode()

Sets the mode of the pin.

```c
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);

   Port->MODER &= ~(3UL<<(2*pin));
   Port->MODER |= mode<<(2*pin);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **mode**: INPUT(0), OUTPUT(1), AF(2), ANALOG(3)

**Example code**

```c
GPIO_mode(pinName, mode);
```

### GPIO_ospeed()

Sets the output speed of the pin.

```c
void GPIO_ospeed(PinName_t pinName, uint32_t speed){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->OSPEEDR &= ~(3UL<<(2*pin));		// clear the 2-bit field
	Port->OSPEEDR |= (speed & 3UL)<<(2*pin);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **speed**: LOW_SPEED(0), MEDIUM(1), FAST(2), HIGH_SPEED(3)

**Example code**

```c
GPIO_ospeed(LED_PIN, MEDIUM);
```

### GPIO_otype()

Sets the output type of the pin.

```c
void GPIO_otype(PinName_t pinName, uint32_t type){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->OTYPER &= ~(1UL<<pin);			// 1 bit per pin
	Port->OTYPER |= (type & 1UL)<<pin;
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **type**: PUSH_PULL(0), OPEN_DRAIN(1)

**Example code**

```c
GPIO_otype(LED_PIN, OPEN_DRAIN);
```

### GPIO_pupd()

Sets the pull-up / pull-down of the pin.

```c
void GPIO_pupd(PinName_t pinName, uint32_t pupd){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->PUPDR &= ~(3UL<<(2*pin));			// clear the 2-bit field
	Port->PUPDR |= (pupd & 3UL)<<(2*pin);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **pupd**: NO_PUPD(0), PULL_UP(1), PULL_DOWN(2)

**Example code**

```c
GPIO_pupd(BUTTON_PIN, PULL_UP);
```

### GPIO_write()

Writes HIGH or LOW to the output pin.

```c
void GPIO_write(PinName_t pinName, uint32_t Output){
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	if (Output) Port->ODR |= (1UL<<pin);	// set   -> HIGH
	else        Port->ODR &= ~(1UL<<pin);	// clear -> LOW
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **Output**: LOW(0), HIGH(1)

**Example code**

```c
if(buttonState)	GPIO_write(LED_PIN, LOW);
else 		GPIO_write(LED_PIN, HIGH);
```

### GPIO_read()

Reads the input pin.

```c
uint32_t GPIO_read(PinName_t pinName){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	uint32_t val=0;
	val = ((Port->IDR) >> pin) & 1UL;		// shift first, then mask -> 0 or 1
	return val;
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)

**Return**

* the value of the pin, LOW(0) or HIGH(1)

**Example code**

```c
buttonState = GPIO_read(BUTTON_PIN);
```

### FND_init()

Sets the segment pins as output.

```c
void FND_init(PinName_t *pinFND){
	for (int i=0; i<8; i++){
		_fndPins[i] = pinFND[i];
		GPIO_init(_fndPins[i], OUTPUT);
	}
}
```

**Parameters**

* **pinFND**: array of 8 segment pins, a~g, dot

**Example code**

```c
FND_init(pinFND);
```

### FND_select_init()

Sets the select pins as output.

```c
void FND_select_init(PinName_t *selectFND){
	for (int i=0; i<4; i++){
		_fndSel[i] = selectFND[i];
		GPIO_init(_fndSel[i], OUTPUT);
	}
}
```

**Parameters**

* **selectFND**: array of 4 select pins, FND_0~FND_3

**Example code**

```c
FND_select_init(selectFND);
```

### FND_display()

Displays a number.

```c
void FND_display(uint8_t num){
	if (num > 11) num = 11;					// out of range -> blank

	for (int i=0; i<8; i++){
		GPIO_write(_fndPins[i], numberFND[num][i]);
	}
}
```

**Parameters**

* **num**: 0~9 number, 10 dot, 11 blank

**Example code**

```c
FND_display(num);
```

### FND_select()

Selects the display digit.

```c
void FND_select(uint8_t digit){
	for (int i=0; i<4; i++){
		if (i == digit){
			GPIO_write(_fndSel[i], HIGH);
		} else {
			GPIO_write(_fndSel[i], LOW);
		}
	}
}
```

**Parameters**

* **digit**: 0~3 (FND_0~FND_3)

**Example code**

```c
FND_select(0);
```

### pinMode()

Initializes GPIO pins.

```c
void pinMode(PinName_t pin, uint32_t mode){
	GPIO_init(pin, mode);
}
```

**Parameters**

* **pin**: pin name (`PinName_t`)
* **mode**: INPUT(0), OUTPUT(1), AF(2), ANALOG(3)

**Example code**

```c
pinMode(LED_PIN, OUTPUT);
```

### digitalWrite()

Writes to the output pin.

```c
void digitalWrite(PinName_t pin, uint32_t value){
	GPIO_write(pin, value);
}
```

**Parameters**

* **pin**: pin name (`PinName_t`)
* **value**: LOW(0), HIGH(1)

**Example code**

```c
digitalWrite(LED_PIN, HIGH);
```

### digitalRead()

Reads the input pin.

```c
uint32_t digitalRead(PinName_t pin){
	return GPIO_read(pin);
}
```

**Parameters**

* **pin**: pin name (`PinName_t`)

**Return**

* the value of the pin, LOW(0) or HIGH(1)

**Example code**

```c
buttonState = digitalRead(BUTTON_PIN);
```

### led_toggle()

Toggles the output pin.

```c
void led_toggle(PinName_t pinName){
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
	Port->ODR ^= 1 << pin;
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)

**Example code**

```c
led_toggle(LED_PIN);
```

---

## SysTick

### Header File

`#include "ecSysTick2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 09-17-2026
Language/ver     : C++ in VS Code

Description      : SysTick Library. Distributed to Students for LAB_SYSTICK
/----------------------------------------------------------------*/


#ifndef __EC_SYSTICK2_H
#define __EC_SYSTICK2_H

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


extern volatile uint32_t msTicks;	

void SysTick_init(void);
void SysTick_Handler(void);
void SysTick_counter(void);
void delay_ms(uint32_t msec);
void SysTick_reset(void);
uint32_t SysTick_val(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_SYSTICK2_H
```

### SysTick_init()

Initializes the SysTick timer and enables the SysTick interrupt.

```c
void SysTick_init(void){
	//  SysTick Control and Status Register
	// Disable SysTick IRQ and SysTick Counter
	SysTick->CTRL = 0;											
	
	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	// SysTick Reload Value Register : (SYSCLK / 1000) - 1  ->  1 ms
	//   HSI 16 MHz :  15999      PLL 84 MHz : 83999 
	SysTick->LOAD = (uint32_t)EC_SYSCLK *1UL/ 1000UL - 1UL;   // 1[ms] = 1/1000[s] 

	// SysTick Current Value Register : Reset counter value to 0
	SysTick->VAL = 0;

	// Enables SysTick exception request
	// 1 = counting down to zero --> SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		
	// Enable interrupt in NVIC
	NVIC_SetPriority(SysTick_IRQn, 15);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);			// Enable interrupt in NVIC
}
```

**Parameters**

* None

**Example code**

```c
RCC_PLL_init();                                 // System Clock = 84MHz
SysTick_init();                                 // Systick init
```

### SysTick_Handler()

Increases the tick count.

```c
void SysTick_Handler(void){
	SysTick_counter();	
}
```

**Parameters**

* None

**Example code**

```c
RCC_PLL_init();                                 // System Clock = 84MHz
SysTick_init();                                 // Systick init
// SysTick_Handler() is called every 1 ms by the SysTick IRQ
```

### SysTick_counter()

Increases the tick count.

```c
void SysTick_counter(void){
	msTicks++;
}
```

**Parameters**

* None

**Example code**

```c
SysTick_counter();	
```

### delay_ms()

Delays in milliseconds.

```c
void delay_ms (uint32_t msec){
  	uint32_t curTicks;
  	curTicks = msTicks;
	while ((msTicks - curTicks) < msec){;}		// unsigned math: safe across wrap-around
}
```

**Parameters**

* **msec**: delay time in milliseconds

**Example code**

```c
delay_ms(1000);                            // wait 1 sec (SysTick)
```

### SysTick_reset()

Resets the SysTick counter.

```c
void SysTick_reset(void)
{
	SysTick->VAL = 0;
}
```

**Parameters**

* None

**Example code**

```c
SysTick_reset();
```

### SysTick_val()

Returns the current value of the SysTick counter.

```c
uint32_t SysTick_val(void) {
	return SysTick->VAL;
}
```

**Parameters**

* None

**Return**

* the current value of the SysTick counter

**Example code**

```c
SysTick_val();
```

---

## EXTI

### Header File

`#include "ecEXTI2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 09-17-2026
Language/ver     : C++ in VS Code

Description      : External Interrupt (EXTI) Library. Distributed to Students for LAB_EXTI
/----------------------------------------------------------------*/

#ifndef __EC_EXTI2_H
#define __EC_EXTI2_H

#include "stm32f411xe.h"
#include "ecPinNames.h"

#define FALL 0
#define RISE 1
#define BOTH 2

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
void EXTI_enable(PinName_t pinName);
void EXTI_disable(PinName_t pinName);
uint32_t is_pending_EXTI(PinName_t pinName);
void clear_pending_EXTI(PinName_t pinName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
	 
#endif // __EC_EXTI2_H
```

### EXTI_init()

Initializes the external interrupt.

```c
void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority){

	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
	
	// Enable EXTI Clock with SYSCFG controller clock 	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;		
	

	// Connect EXTI to the GPIO Port_y Pin_x
	// Pin 0~3: EXTICR1 // EXTICR[0]
	// Pin 4~7: EXTICR2 // EXTICR[1]
	// Pin 8~11: EXTICR3 // EXTICR[2]
	// Pin 12~15: EXTICR4 // EXTICR[3]	
	uint32_t EXTICR_port=0;
	if		(Port == GPIOA) EXTICR_port = 0;
	else if	(Port == GPIOB) EXTICR_port = 1;
	else if	(Port == GPIOC) EXTICR_port = 2;
	else if	(Port == GPIOD) EXTICR_port = 3;
	else					EXTICR_port = 4;
	
	SYSCFG->EXTICR[pin/4] &= ~(0xFUL << (4*(pin%4)));			// clear 4 bits
	SYSCFG->EXTICR[pin/4] |= EXTICR_port << (4*(pin%4));			// Set 4 bits
	

	// Select  Trigger edge (RISE, FALL, BOTH)
	if (trig_type == FALL) 		EXTI->FTSR |= 1UL << pin;  // Falling trigger enable 
	else if	(trig_type == RISE) EXTI->RTSR |= 1UL << pin;   // Rising trigger enable 
	else if	(trig_type == BOTH) {			// Both falling/rising trigger enable
		EXTI->RTSR |= 1UL << pin; 
		EXTI->FTSR |= 1UL << pin;
	} 
	
	// Enable EXTI, with Not-Masked Interrupt Request 
	// Not-mask (==Enable) EXTIx
 	EXTI->IMR |= 1UL << pin;
	
	
	// NVIC(IRQ) Setting
	uint32_t EXTI_IRQn = 0;
	if (pin < 5) 		EXTI_IRQn = EXTI0_IRQn + pin;
	else if	(pin < 10) 	EXTI_IRQn = EXTI9_5_IRQn;
	else 				EXTI_IRQn = EXTI15_10_IRQn;
		
	NVIC_SetPriority(EXTI_IRQn, priority);	
	NVIC_EnableIRQ(EXTI_IRQn); 				
}
```

**Parameters**

* **pinName**: pin name
* **trig_type**: FALL(0), RISE(1), BOTH(2)
* **priority**: 0~15, a smaller number is a higher priority

**Example code**

```c
// Initialize EXTI PD_2, PA_4
EXTI_init(SW1_PIN, FALL, 10);
EXTI_init(SW2_PIN, FALL, 10);
```

### EXTI_enable()

Enables the interrupt of the pin.

```c
void EXTI_enable(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
	
	EXTI->IMR |= 1UL << pin;     // not masked (i.e., Interrupt enabled)
}
```

**Parameters**

* **pinName**: pin name

**Example code**

```c
EXTI_enable(SW2_PIN);
```

### EXTI_disable()

Disables the interrupt of the pin.

```c
void EXTI_disable(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	EXTI->IMR &= ~(1UL << pin);     // masked (i.e., Interrupt disabled)
}
```

**Parameters**

* **pinName**: pin name

**Example code**

```c
EXTI_disable(SW2_PIN);
```

### is_pending_EXTI()

Returns the pending bit of the pin.

```c
uint32_t is_pending_EXTI(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	uint32_t EXTI_PRx =  (EXTI->PR >> pin) & 1;     // read PRx, EXTI pending bit.  Use  (REG>>k & 1) to read.
	return  EXTI_PRx; 	// Return only 0 or 1
}
```

**Parameters**

* **pinName**: pin name

**Return**

* the pending bit of the pin, 0 or 1

**Example code**

```c
if (is_pending_EXTI(SW2_PIN)) {
		paused ^= 1;                       // 1: paused, 0: counting
		clear_pending_EXTI(SW2_PIN);
}
```

### clear_pending_EXTI()

Clears the pending bit of the pin.

```c
void clear_pending_EXTI(PinName_t pinName){
	// Port, Pin Configuration
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	// clear by writing 1 to the pending bit
	EXTI->PR  |= (1 << pin);     
}
```

**Parameters**

* **pinName**: pin name

**Example code**

```c
clear_pending_EXTI(SW2_PIN);
```

---

## Stepper Motor

### Header File

`#include "ecStepper2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 10-10-2026
Language/ver     : C++ in VS Code

Description      : Stepper Library. Distributed to Students for LAB_Stepper_Motor
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
			
#ifndef __EC_STEPPER2_H
#define __EC_STEPPER2_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

// Stepper Mode
#define HALF 0
#define FULL 1	 
#define DIR_CW 0
#define DIR_CCW 1	  

// Stepper Motor Spec
// 28BYJ-48 : 64 steps/rev x 1/32 gear = 2048 
#define STEP_PER_REV  (64*32)		

//State number 
typedef enum {
	S0, S1, S2, S3, S4, S5, S6, S7
} StateNum;

// FULL stepping sequence  - FSM
typedef struct {	
  uint32_t next[2];
  uint8_t out[4];
} StateStepper_t;

// Initialization of Stepper Motor
void stepper_init(uint32_t mode, PinName_t *pinStepper);

// Converts Motor [rpm] to step delay in [msec]
void stepper_speed (uint32_t speedRPM);

// Run Stepper Motor for given steps and direction
void stepper_step(uint32_t steps, uint32_t direction);

// Stepper Motor Output for given state
void stepper_out(uint32_t state);

// Stop Stepper Motor
void stepper_stop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_STEPPER2_H
```

### stepper_init()

Initializes the stepper motor.

```c
void stepper_init(uint32_t mode, PinName_t *pinStepper){
	if (mode == HALF) 
		fsm = fsm_Half;
	else
		fsm = fsm_Full;

	//  GPIO Digital Out Initiation
	// For A, B, AN, BN

	for (int i=0; i<4; i++){
		stepperPins[i] = pinStepper[i];
		GPIO_init(stepperPins[i], OUTPUT);
		GPIO_ospeed(stepperPins[i], FAST);
	}
}
```

**Parameters**

* **mode**: HALF(0), FULL(1)
* **pinStepper**: the four pins in the order A, B, A', B'

**Example code**

```c
stepper_init(FULL, pinStepper); 				// Stepper GPIO pin initialization
```

### stepper_speed()

Converts the speed in rpm to the delay of one step in msec.

```c
void stepper_speed (uint32_t speedRPM){      // rpm
		_step_delay = 60*1000/(STEP_PER_REV*speedRPM); 		//in [msec]	
		// [usec] can be used for a higher accuracy
		// But needs delay_us() 
}
```

**Parameters**

* **speedRPM**: speed in rpm

**Example code**

```c
stepper_speed(1);                          		//  set stepper motor speed
```

### stepper_step()

Rotates the motor for the given number of steps in the given direction.

```c
void stepper_step(uint32_t steps, uint32_t direction){
	// Exit if stepper_init() not called 
	if (fsm == 0) return;
	_steps = steps;

	// run for step size: 
	for (uint32_t i = 0; i < _steps; i++){
		// Update Present State
		state = fsm[state].next[direction];
		
		// Output of Present State
		stepper_out(state);
	
		// Delay for steppermotor speed
		delay_ms(_step_delay);
	}
}
```

**Parameters**

* **steps**: number of steps
* **direction**: DIR_CW(0), DIR_CCW(1)

**Example code**

```c
stepper_step(steps, DIR_CW);  // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
```

### stepper_out()

Writes the state output to the pins.

```c
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...

	for (int i=0; i<4; i++)
		GPIO_write(stepperPins[i], fsm[state].out[i]);
}
```

**Parameters**

* **state**: state number

**Example code**

```c
stepper_out(state);
```

### stepper_stop()

Stops the motor.

```c
void stepper_stop(void) {
    _steps = 0;    
    
	// All pins DigitalOut '0'
	for (int i=0; i<4; i++)
		GPIO_write(stepperPins[i], LOW);
}
```

**Parameters**

* None

**Example code**

```c
stepper_stop();
```

---

## USART

### Header File

`#include "ecUART2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 10-08-2025
Modified         : 10-19-2026
Language/ver     : C in VS Code

Description      : USART2  library
/----------------------------------------------------------------*/

#ifndef __EC_USART2_STUDENT_H
#define __EC_USART2_STUDENT_H

#include <stdio.h>
#include <math.h>
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"


#define POL 0
#define INT 1

// You can modify this
#define BAUD_9600	9600
#define BAUD_19200	19200
#define BAUD_38400  38400
#define BAUD_57600	57600
#define BAUD_115200 115200
#define BAUD_921600 921600


// ********************** USART 2 (USB) ***************************
	// PA_2 = USART2_TX
	// PA_3 = USART2_RX
	// Alternate function(AF7), High Speed, Push pull, Pull up
	// APB1
// **********************************************************

// ********************** USART 1 ***************************
	// PA_9 = USART1_TX (default)	// PB_6  (option)
	// PA_10 = USART1_RX (default)	// PB_3 (option)
	// APB2
// **********************************************************

// ********************** USART 6 ***************************
	// PA_11 = USART6_TX (default)	// PC_6  (option)
	// PA_12 = USART6_RX (default)	// PC_7 (option)
	// APB2
// **********************************************************


/*================ EXERCISE ================*/
/*================ General Configuration ================*/
// General configuration
void USART_init(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX, uint32_t baud);	// copy of USART_setting
void USART_baud(USART_TypeDef* USARTx, uint32_t baud);
void USART_pins(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX);

void USART1_baud(uint32_t baud);
void USART2_baud(uint32_t baud);


/*================ PROVIDED  ================*/
/*================ Configuration for each USART ================*/
// Configuration UART 1, 2 using default settings
void USART1_init(void);
void USART2_init(void);

// USART write & read
void USART1_write(uint8_t* buffer, uint32_t nBytes);
void USART2_write(uint8_t* buffer, uint32_t nBytes);
uint8_t USART1_read(void);										
uint8_t USART2_read(void);	

// RX Inturrupt Flag USART1,2
uint32_t is_USART1_RXNE(void);
uint32_t is_USART2_RXNE(void);


/*================ General Configuration ================*/
void USART_clock_enable(USART_TypeDef* USARTx);
void USART_write(USART_TypeDef* USARTx, uint8_t* buffer, uint32_t nBytes);
uint8_t USART_read(USART_TypeDef * USARTx);										
uint32_t is_USART_RXNE(USART_TypeDef * USARTx);
void USART_delay(uint32_t us);  

								

#endif // __EC_USART2_STUDENT_H
```

### USART_init()

Initializes the USART with the given TX and RX pins and baud rate, and enables its RX interrupt.

```c
void USART_init(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX, uint32_t baud){
//1. GPIO Pin for TX and RX
	USART_pins(USARTx, pin_GPIO_TX, pin_GPIO_RX);

//2. USARTx (x=2,1,6) configuration
	USART_clock_enable(USARTx);

	// Disable USARTx.
	USARTx->CR1 &= ~USART_CR1_UE; 	// USART disable

	// No Parity / 8-bit word length / Oversampling x16 / Stop bit =1
	USARTx->CR1 &= ~USART_CR1_M;			// 8 data bits
	USARTx->CR1 &= ~USART_CR1_PCE;			// no parity
	USARTx->CR1 &= ~USART_CR1_OVER8;		// oversampling by 16
	USARTx->CR2 &= ~USART_CR2_STOP;			// 1 stop bit

	// Set Baudrate using APB frequency (42MHz)
	// If oversampling by 16, Tx/Rx baud = f_CK / (16*USARTDIV),
	// If oversampling by 8,  Tx/Rx baud = f_CK / (8*USARTDIV)
	USART_baud(USARTx, baud);

	// Enable TX, RX, and USARTx
	USARTx->CR1 |= (USART_CR1_RE | USART_CR1_TE);   	// Transmitter and Receiver enable
	USARTx->CR1 |= USART_CR1_UE; 						          // USART enable

// 3. RX interrupt (data ready to be read)
  // Enable RXNE interrupt
	USARTx->CR1 |= USART_CR1_RXNEIE;
  // USART_IRQn
	uint32_t USART_IRQ = USART2_IRQn;
  // Set the priority and enable interrupt
	if (USARTx == USART1)		USART_IRQ = USART1_IRQn;
	else if (USARTx == USART6)	USART_IRQ = USART6_IRQn;
 
	NVIC_SetPriority(USART_IRQ, 1);
	NVIC_EnableIRQ(USART_IRQ);

}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6
* **pin_GPIO_TX**: TX pin of the USART
* **pin_GPIO_RX**: RX pin of the USART
* **baud**: baud rate (BAUD_9600, BAUD_19200, BAUD_38400, BAUD_57600, BAUD_115200, BAUD_921600)

**Example code**

```c
USART_init(USART2, PA_2, PA_3, BAUD_57600);	
```

### USART_baud()

Sets the baud rate of the USART.

```c
void USART_baud(USART_TypeDef* USARTx, uint32_t baud){
	// Disable USARTx.
	USARTx->CR1  &= ~USART_CR1_UE; 						// USART disable
	USARTx->BRR = 0;

	// Configure Baud-rate
	float fCK = EC_SYSCLK;                                   // if(USARTx==USART1 || USARTx==USART6), APB2
	                                                         // (84MHz after RCC_PLL_init(), 16MHz after RCC_HSI_init())
	if(USARTx == USART2) fCK =fCK/2;      // APB1
  float USARTDIV = (float) fCK/16.0/baud;

	// Method 1 : build the two BRR fields explicitly
	//   BRR[15:4] = DIV_Mantissa (integer part of USARTDIV)
	//   BRR[3:0]  = DIV_Fraction (counts 1/16 steps -> multiply the fraction by 16)
  uint32_t MNT   = (uint32_t)USARTDIV;
  uint32_t FRC   = round((USARTDIV - MNT) * 16);
	if (FRC > 15) { MNT += 1; FRC = 0; }		// carry into the mantissa
	USARTx->BRR = (MNT << 4) | FRC;

  
	// Enable TX, RX, and USARTx
	USARTx->CR1 |= USART_CR1_UE;
}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6
* **baud**: baud rate (BAUD_9600, BAUD_19200, BAUD_38400, BAUD_57600, BAUD_115200, BAUD_921600)

**Example code**

```c
USART_baud(USARTx, baud);
```

### USART_pins()

Sets the TX and RX pins as alternate function pins of the USART.

```c
void USART_pins(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX){
	GPIO_TypeDef *GPIO_TX;
	unsigned int pinTX;
	ecPinmap(pin_GPIO_TX, &GPIO_TX, &pinTX);

	GPIO_TypeDef *GPIO_RX;
	unsigned int pinRX;
	ecPinmap(pin_GPIO_RX, &GPIO_RX, &pinRX);

	// Alternate Function, Push-Pull, No Pull-up/down, High speed
	GPIO_init(pin_GPIO_TX, AF);
	GPIO_otype(pin_GPIO_TX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_TX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_TX, HIGH_SPEED);

	GPIO_init(pin_GPIO_RX, AF);
	GPIO_otype(pin_GPIO_RX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_RX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_RX, HIGH_SPEED);

	// Set Alternate Function Register for USARTx
	//   AF7 - USART1, USART2
	//   AF8 - USART6
	uint32_t AF_num = (USARTx == USART6) ? 8 : 7;
	if (pinTX < 8) { GPIO_TX->AFR[0] &= ~(0xFUL << (4*pinTX));     GPIO_TX->AFR[0] |= AF_num << (4*pinTX); }
	else           { GPIO_TX->AFR[1] &= ~(0xFUL << (4*(pinTX-8))); GPIO_TX->AFR[1] |= AF_num << (4*(pinTX-8)); }
	
  if (pinRX < 8) {
    GPIO_RX->AFR[0] &= ~(0xFUL << (4*pinRX));
    GPIO_RX->AFR[0] |= AF_num << (4*pinRX);
  }
  else{
    GPIO_RX->AFR[1] &= ~(0xFUL << (4*(pinRX-8)));
    GPIO_RX->AFR[1] |= AF_num << (4*(pinRX-8));
  }

}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6
* **pin_GPIO_TX**: TX pin of the USART
* **pin_GPIO_RX**: RX pin of the USART

**Example code**

```c
USART_pins(USARTx, pin_GPIO_TX, pin_GPIO_RX);
```

### USART1_baud()

Sets the baud rate of USART1.

```c
void USART1_baud(uint32_t baud){
	USART_baud(USART1, baud);
}
```

**Parameters**

* **baud**: baud rate (BAUD_9600, BAUD_19200, BAUD_38400, BAUD_57600, BAUD_115200, BAUD_921600)

**Example code**

```c
USART1_baud(BAUD_9600);
```

### USART2_baud()

Sets the baud rate of USART2.

```c
void USART2_baud(uint32_t baud){
	USART_baud(USART2, baud);
}
```

**Parameters**

* **baud**: baud rate (BAUD_9600, BAUD_19200, BAUD_38400, BAUD_57600, BAUD_115200, BAUD_921600)

**Example code**

```c
USART2_baud(BAUD_38400);
```

### USART1_init()

Initializes USART1 with the default setting.

```c
void USART1_init(void){
	// ********************** USART 1 ***************************
	// PA_9 = USART1_TX (default)	// PB_6  (option)
	// PA_10 = USART1_RX (default)	// PB_3 (option)
	// APB2
	// **********************************************************
	//USART_init(USART1, PA_9, PA_10, 9600);

  ////////////////////////////////////////////
  //  for USART1  ONLY
  ////////////////////////////////////////////
  USART_TypeDef *USARTx= USART1;

//1. GPIO Pin for TX and RX
// Default : PA_9 = USART1_TX, PA_10 = USART1_RX
	PinName_t pin_GPIO_TX  =PA_9;
	PinName_t pin_GPIO_RX  =PA_10;

	GPIO_TypeDef *GPIO_TX;
	unsigned int pinTX;
	ecPinmap(pin_GPIO_TX, &GPIO_TX, &pinTX);
	GPIO_TypeDef *GPIO_RX;
	unsigned int pinRX;
	ecPinmap(pin_GPIO_RX, &GPIO_RX, &pinRX);

	// Alternate Function, Push-Pull, No Pull-up/down, High speed
	GPIO_init(pin_GPIO_TX, AF);
	GPIO_otype(pin_GPIO_TX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_TX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_TX, HIGH_SPEED);

	GPIO_init(pin_GPIO_RX, AF);
	GPIO_otype(pin_GPIO_RX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_RX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_RX, HIGH_SPEED);

 	// Set Alternate Function Register for USARTx
	//   AF7 - USART1, USART2
	//   AF8 - USART6
	uint32_t AF_num = (USARTx == USART6) ? 8 : 7;
	if (pinTX < 8) { GPIO_TX->AFR[0] &= ~(0xFUL << (4*pinTX));     GPIO_TX->AFR[0] |= AF_num << (4*pinTX); }
	else           { GPIO_TX->AFR[1] &= ~(0xFUL << (4*(pinTX-8))); GPIO_TX->AFR[1] |= AF_num << (4*(pinTX-8)); }
	if (pinRX < 8) { GPIO_RX->AFR[0] &= ~(0xFUL << (4*pinRX));     GPIO_RX->AFR[0] |= AF_num << (4*pinRX); }
	else           { GPIO_RX->AFR[1] &= ~(0xFUL << (4*(pinRX-8))); GPIO_RX->AFR[1] |= AF_num << (4*(pinRX-8)); }


//2. USARTx (x=2,1,6) configuration
  // Enable USART peripheral clock
  	//      USART2   = APB1
  	//      USART1,6 = APB2
	USART_clock_enable(USARTx);

  // Disable USARTx.
	USARTx->CR1 &= ~USART_CR1_UE;			// disable while configuring

  // No Parity / 8-bit word length / Oversampling x16
	USARTx->CR1 &= ~USART_CR1_M;			// 8 data bits
	USARTx->CR1 &= ~USART_CR1_PCE;			// no parity
	USARTx->CR1 &= ~USART_CR1_OVER8;		// oversampling by 16
	USARTx->CR2 &= ~USART_CR2_STOP;			// 1 stop bit

  // BAUD RATE (Default: 9600)
  //    Baud rate : BRR[15:4]=mantissa, BRR[3:0]=fraction (1/16 steps)
  //    USARTDIV = f_APB1 / (16 x baud)
  //    USART_baud(USARTx, 9600);
  uint32_t baud=  9600;				// Default baud rate for USART2
  // For USART2:
  //float fCK      = (float)EC_SYSCLK / 2;		// APB1 : 84MHz PLL -> 42MHz
  // For USART1:
  float fCK      = (float)EC_SYSCLK;			// APB2 : 84MHz PLL -> 84MHz
  float USARTDIV = fCK / 16 / baud;
  uint32_t MNT   = (uint32_t)USARTDIV;
  uint32_t FRC   = round((USARTDIV - MNT) * 16);
	if (FRC > 15) { MNT += 1; FRC = 0; }		// carry into the mantissa
	USARTx->BRR = (MNT << 4) | FRC;

  // Enable TX, RX
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);	// transmitter + receiver
  // Enable USART
  	USARTx->CR1 |= USART_CR1_UE;

// 3. RX interrupt (data ready to be read)
  // Enable RXNE interrupt
	USARTx->CR1 |= USART_CR1_RXNEIE;
  // USART2 IRQ
	uint32_t USART_IRQ = USART2_IRQn;
	if (USARTx == USART1){
		USART_IRQ = USART1_IRQn;
	}
	NVIC_SetPriority(USART_IRQ, 1);
	NVIC_EnableIRQ(USART_IRQ);
}
```

**Parameters**

* None

**Example code**

```c
USART1_init();
```

### USART2_init()

Initializes USART2 (USB, ST-Link) with the default setting.

```c
void USART2_init(void){
// ********************** USART 2 ***************************
// PA2 = USART2_TX
// PA3 = USART2_RX
// Alternate function(AF7), High Speed, Push pull, Pull up
// **********************************************************
// USART_init(USART2, PA_2, PA_3, 9600);

////////////////////////////////////////////
//  for USART2  ONLY
////////////////////////////////////////////
  USART_TypeDef *USARTx= USART2;

//1. GPIO Pin for TX and RX
// Default : PA_2 = USART2_TX, PA_3 = USART2_RX
	PinName_t pin_GPIO_TX  =PA_2;
	PinName_t pin_GPIO_RX  =PA_3;

	GPIO_TypeDef *GPIO_TX;
	unsigned int pinTX;
	ecPinmap(pin_GPIO_TX, &GPIO_TX, &pinTX);
	GPIO_TypeDef *GPIO_RX;
	unsigned int pinRX;
	ecPinmap(pin_GPIO_RX, &GPIO_RX, &pinRX);

	// Alternate Function, Push-Pull, No Pull-up/down, High speed
	GPIO_init(pin_GPIO_TX, AF);	
	GPIO_otype(pin_GPIO_TX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_TX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_TX, HIGH_SPEED);

	GPIO_init(pin_GPIO_RX, AF);
	GPIO_otype(pin_GPIO_RX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_RX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_RX, HIGH_SPEED);

 	// Set Alternate Function Register for USARTx
	//   AF7 - USART1, USART2
	//   AF8 - USART6
	uint32_t AF_num = (USARTx == USART6) ? 8 : 7;
	if (pinTX < 8) { GPIO_TX->AFR[0] &= ~(0xFUL << (4*pinTX));     GPIO_TX->AFR[0] |= AF_num << (4*pinTX); }
	else           { GPIO_TX->AFR[1] &= ~(0xFUL << (4*(pinTX-8))); GPIO_TX->AFR[1] |= AF_num << (4*(pinTX-8)); }
	if (pinRX < 8) { GPIO_RX->AFR[0] &= ~(0xFUL << (4*pinRX));     GPIO_RX->AFR[0] |= AF_num << (4*pinRX); }
	else           { GPIO_RX->AFR[1] &= ~(0xFUL << (4*(pinRX-8))); GPIO_RX->AFR[1] |= AF_num << (4*(pinRX-8)); }


//2. USARTx (x=2,1,6) configuration
  // Enable USART peripheral clock
  	//      USART2   = APB1
  	//      USART1,6 = APB2
	USART_clock_enable(USARTx);

  // Disable USARTx.
	USARTx->CR1 &= ~USART_CR1_UE;			// disable while configuring

  // No Parity / 8-bit word length / Oversampling x16
	USARTx->CR1 &= ~USART_CR1_M;			// 8 data bits
	USARTx->CR1 &= ~USART_CR1_PCE;			// no parity
	USARTx->CR1 &= ~USART_CR1_OVER8;		// oversampling by 16
	USARTx->CR2 &= ~USART_CR2_STOP;			// 1 stop bit

  // BAUD RATE (Default: 9600)
  //    Baud rate : BRR[15:4]=mantissa, BRR[3:0]=fraction (1/16 steps)
  //    USARTDIV = f_APB1 / (16 x baud)
  //    USART_baud(USARTx, 9600);
  uint32_t baud=  9600;				// Default baud rate for USART2
  float fCK      = (float)EC_SYSCLK / 2;		// APB1 : 84MHz PLL -> 42MHz
  float USARTDIV = fCK / 16 / baud;
  uint32_t MNT   = (uint32_t)USARTDIV;
  uint32_t FRC   = round((USARTDIV - MNT) * 16);
	if (FRC > 15) { MNT += 1; FRC = 0; }		// carry into the mantissa
	USARTx->BRR = (MNT << 4) | FRC;

  // Enable TX, RX
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);	// transmitter + receiver
  // Enable USART
  	USARTx->CR1 |= USART_CR1_UE;

// 3. RX interrupt (data ready to be read)
  // Enable RXNE interrupt
	USARTx->CR1 |= USART_CR1_RXNEIE;
  // USART2 IRQ
	uint32_t USART_IRQ = USART2_IRQn;
	if (USARTx == USART1){
		USART_IRQ = USART1_IRQn;
	}
	NVIC_SetPriority(USART_IRQ, 1);
	NVIC_EnableIRQ(USART_IRQ);
}
```

**Parameters**

* None

**Example code**

```c
USART2_init();
```

### USART1_write()

Sends data through USART1.

```c
void USART1_write(uint8_t* buffer, uint32_t nBytes){
	USART_write(USART1, buffer, nBytes);
}
```

**Parameters**

* **buffer**: data to send
* **nBytes**: number of bytes to send

**Example code**

```c
USART1_write(&PC_data,1);    // TX to Other MCU
```

### USART2_write()

Sends data through USART2.

```c
void USART2_write(uint8_t* buffer, uint32_t nBytes){
	USART_write(USART2, buffer, nBytes);
}
```

**Parameters**

* **buffer**: data to send
* **nBytes**: number of bytes to send

**Example code**

```c
USART2_write(PC_string, sizeof(PC_string));
```

### USART1_read()

Reads the data received by USART1.

```c
uint8_t USART1_read(void){
	return USART_read(USART1);
}
```

**Parameters**

* None

**Return**

* the received data (8 bits)

**Example code**

```c
BT_Data = USART1_read();				// RX from BT
```

### USART2_read()

Reads the data received by USART2.

```c
uint8_t USART2_read(void){
	return USART_read(USART2);
}
```

**Parameters**

* None

**Return**

* the received data (8 bits)

**Example code**

```c
PC_data = USART2_read();     // RX from UART2 (PC)
```

### is_USART1_RXNE()

Checks if USART1 has received data.

```c
uint32_t is_USART1_RXNE(void){
	return is_USART_RXNE(USART1);
}
```

**Parameters**

* None

**Return**

* 1 if RXNE is set (the received data is ready to read), 0 if not

**Example code**

```c
if(is_USART1_RXNE()){
```

### is_USART2_RXNE()

Checks if USART2 has received data.

```c
uint32_t is_USART2_RXNE(void){
	return is_USART_RXNE(USART2);
}
```

**Parameters**

* None

**Return**

* 1 if RXNE is set (the received data is ready to read), 0 if not

**Example code**

```c
if(is_USART2_RXNE()){
```

### USART_clock_enable()

Enables the peripheral clock of the USART.

```c
void USART_clock_enable(USART_TypeDef* USARTx){
	if (USARTx == USART1)
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 	// Enable USART 1 clock (APB2 clock: AHB clock = 84MHz)
	else if(USARTx == USART2)
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  	// Enable USART 2 clock (APB1 clock: AHB clock/2 = 42MHz)
	else
		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;  	// Enable USART 6 clock (APB2 clock: AHB clock = 84MHz)
}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6

**Example code**

```c
USART_clock_enable(USARTx);
```

### USART_write()

Sends data through the USART with polling.

```c
void USART_write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	// TXE is set by hardware when the content of the TDR
	// register has been transferred into the shift register.
	int i;
	for (i = 0; i < nBytes; i++) {
		// wait until TXE (TX empty) bit is set
		while (!(USARTx->SR & USART_SR_TXE));
		// Writing USART_DR automatically clears the TXE flag
		USARTx->DR = buffer[i] & 0xFF;
		USART_delay(300);
	}
	// wait until TC bit is set
	while (!(USARTx->SR & USART_SR_TC));
	// TC bit clear
	USARTx->SR &= ~USART_SR_TC;
}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6
* **buffer**: data to send
* **nBytes**: number of bytes to send

**Example code**

```c
USART_write(USART1, buffer, nBytes);
```

### USART_read()

Reads the data received by the USART.

```c
uint8_t USART_read(USART_TypeDef * USARTx){
	// Wait until RXNE (RX not empty) bit is set by HW -->Read to read
	while (is_USART_RXNE(USARTx) == 0);
	// Reading USART_DR automatically clears the RXNE flag
	return ((uint8_t)(USARTx->DR & 0xFF));
}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6

**Return**

* the received data (8 bits)

**Example code**

```c
return USART_read(USART1);
```

### is_USART_RXNE()

Checks if the USART has received data.

```c
uint32_t is_USART_RXNE(USART_TypeDef * USARTx){
	return (USARTx->SR & USART_SR_RXNE) != 0;
}
```

**Parameters**

* **USARTx**: USART1, USART2, USART6

**Return**

* 1 if RXNE is set (the received data is ready to read), 0 if not

**Example code**

```c
while (is_USART_RXNE(USARTx) == 0);
```

### USART_delay()

Waits in a software loop.

```c
void USART_delay(uint32_t us) {
   uint32_t time = 100*us/7;
   while(--time);
}
```

**Parameters**

* **us**: delay value

**Example code**

```c
USART_delay(300);
```

---

## Timer

### Header File

`#include "ecTIM2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 10-26-2026
Language/ver     : C++ in VS Code

Description      : Timer Library. Distributed to Students for PreLAB Timer Interrupt & PWM
/----------------------------------------------------------------*/

#ifndef __EC_TIM2_H
#define __EC_TIM2_H

#include "stm32f411xe.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "math.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


//////////////////////////////////////////////
/* Timer Update Interrupt Configuration     */
//////////////////////////////////////////////

// Timer Update Interrupt Initialization
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec);     // 16-bit  msec < 65,530 msec 
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec);  // 16-bit  usec < 65,530 usec 

// Timer Update Interrupt On/OFf
void TIM_UI_enable(TIM_TypeDef* TIMx);
void TIM_UI_disable(TIM_TypeDef* TIMx);

// Timer Update Interrupt Flag
uint32_t is_UIF(TIM_TypeDef *TIMx);
void clear_UIF(TIM_TypeDef *TIMx);


////////////////////////////////////////////////////////////////
/* Timer Counter Initialization                              */
////////////////////////////////////////////////////////////////

// Timer Counter Initialization
void TIM_init(TIM_TypeDef *TIMx, uint32_t msec); 
void TIM_init_us(TIM_TypeDef *TIMx, uint32_t usec); 

// Timer Counter Period Config
void TIM_period(TIM_TypeDef* TIMx, uint32_t msec);		
void TIM_period_ms(TIM_TypeDef* TIMx, uint32_t msec); 	// same as TIM_period()
void TIM_period_us(TIM_TypeDef* TIMx, uint32_t usec);  	

// Timer Counter Auxiliary Functions
uint32_t get_TIM_IRQn(TIM_TypeDef* TIMx);
void TIM_clock_enable(TIM_TypeDef* TIMx);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_TIM2_H 
```

### TIM_UI_init()

Initializes the timer and enables the update interrupt. The period is in msec.

```c
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec){
// 1. Initialize Timer	
	TIM_init(TIMx,msec);

// 2. Enable Update Interrupt
	TIM_UI_enable(TIMx);	

// 3. NVIC Setting
	uint32_t IRQn_reg = get_TIM_IRQn(TIMx);
	NVIC_EnableIRQ(IRQn_reg);				
	NVIC_SetPriority(IRQn_reg,2);
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **msec**: period in msec

**Example code**

```c
TIM_UI_init(TIM3, 500);
```

### TIM_UI_init_us()

Initializes the timer and enables the update interrupt. The period is in usec.

```c
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec){
// 1. Initialize Timer	
	TIM_init_us(TIMx,usec);
	
// 2. Enable Update Interrupt
	TIM_UI_enable(TIMx);
	
// 3. NVIC Setting
	uint32_t IRQn_reg = get_TIM_IRQn(TIMx);
	NVIC_EnableIRQ(IRQn_reg);				
	NVIC_SetPriority(IRQn_reg,2);
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **usec**: period in usec

**Example code**

```c
TIM_UI_init_us(TIMx, 1);        // TIMx Interrupt initialize at 1us=1MHz
```

### TIM_UI_enable()

Enables the timer update interrupt.

```c
void TIM_UI_enable(TIM_TypeDef* TIMx){
	TIMx->SR = ~TIM_SR_UIF;
	TIMx->DIER |= TIM_DIER_UIE;				
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11

**Example code**

```c
TIM_UI_enable(TIMx);	
```

### TIM_UI_disable()

Disables the timer update interrupt.

```c
void TIM_UI_disable(TIM_TypeDef* TIMx){
	TIMx->DIER &= ~(TIM_DIER_UIE);					
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11

**Example code**

```c
TIM_UI_disable(TIM3);
```

### is_UIF()

Checks the update interrupt flag.

```c
uint32_t is_UIF(TIM_TypeDef *TIMx){
	return TIMx->SR & TIM_SR_UIF;
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11

**Return**

* not 0 if the update interrupt flag is set, 0 if not

**Example code**

```c
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
```

### clear_UIF()

Clears the update interrupt flag.

```c
void clear_UIF(TIM_TypeDef *TIMx){
	TIMx->SR &= ~TIM_SR_UIF;
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11

**Example code**

```c
clear_UIF(TIM3);						// Clear TIM_UI flag
```

### TIM_init()

Initializes the timer counter. The period is in msec.

```c
void TIM_init(TIM_TypeDef* TIMx, uint32_t msec){ 
// 1. Enable Timer CLOCK
	TIM_clock_enable(TIMx);

// 2. Set CNT period
	TIM_period_ms(TIMx, msec); 			

// 3. COUNTER Direction
	// Up-Counter	
	TIMx->CR1 &= ~TIM_CR1_DIR;
	
	// Down-Counter
	//TIMx->CR1 |= TIM_CR1_DIR;

// 4. Enable Timer Counter
	TIMx->CR1 |= TIM_CR1_CEN;		
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **msec**: period in msec

**Example code**

```c
TIM_init(TIMx,msec);
```

### TIM_init_us()

Initializes the timer counter. The period is in usec.

```c
void TIM_init_us(TIM_TypeDef* TIMx, uint32_t usec){ 
// 1. Enable Timer CLOCK
	TIM_clock_enable(TIMx);

// 2. Set CNT period
	TIM_period_us(TIMx, usec); 

// 3. CNT Direction
	TIMx->CR1 &= ~TIM_CR1_DIR;

// 4. Enable Timer Counter
	TIMx->CR1 |= TIM_CR1_CEN;
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **usec**: period in usec

**Example code**

```c
TIM_init_us(TIMx,usec);
```

### TIM_period()

Sets the timer period in msec.

```c
void TIM_period(TIM_TypeDef* TIMx, uint32_t msec){

	uint32_t Sys_CLK = EC_SYSCLK;					// 84MHz (PLL) or 16MHz (HSI)

	// Counter Frequency (f_cnt) 
	uint32_t f_cnt   =  10000UL;					// 16-bit CNT: f_cnt=10kHz (default)
	
	// Prescaler Value
	uint32_t PSCval = Sys_CLK / f_cnt;				// 84MHz -> 10 kHz (PSC=8400)
	TIMx->PSC = PSCval - 1;

	// Reload Value (ARR) for msec unit
	uint32_t ARRval = (f_cnt / 1000UL) * msec;		// Reload values needed for msec 	
	TIMx->ARR = ARRval - 1;
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **msec**: period in msec

**Example code**

```c
TIM_period(TIMx, msec);
```

### TIM_period_ms()

Sets the timer period in msec.

```c
void TIM_period_ms(TIM_TypeDef* TIMx, uint32_t msec){
	TIM_period(TIMx, msec);
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **msec**: period in msec

**Example code**

```c
TIM_period_ms(TIMx, msec); 			
```

### TIM_period_us()

Sets the timer period in usec.

```c
void TIM_period_us(TIM_TypeDef* TIMx, uint32_t usec){

	uint32_t Sys_CLK = EC_SYSCLK;					// 84MHz (PLL) or 16MHz (HSI)
	uint32_t ARRval=0;

	// Counter Frequency (f_cnt) 
	uint32_t f_cnt   =  1000000UL;					// 16-bit CNT: f_cnt=1MHz (default)
	
	// Prescaler Value
	uint32_t PSCval = Sys_CLK / f_cnt;				// 84MHz -> 1 MHz (PSC=84)
	TIMx->PSC = PSCval - 1;

	// Reload Value (ARR) for msec unit
	ARRval = (f_cnt / 1000000UL) * usec;
	TIMx->ARR = ARRval - 1;
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11
* **usec**: period in usec

**Example code**

```c
TIM_period_us(TIMx, usec); 
```

### get_TIM_IRQn()

Finds the IRQ number of the timer.

```c
uint32_t get_TIM_IRQn(TIM_TypeDef* TIMx){
	uint32_t IRQn_reg = 0x00000000;
	if(TIMx == TIM1)       IRQn_reg = TIM1_UP_TIM10_IRQn;
	else if(TIMx == TIM2)  IRQn_reg = TIM2_IRQn;
	else if(TIMx == TIM3)  IRQn_reg = TIM3_IRQn;
	else if(TIMx == TIM4)  IRQn_reg = TIM4_IRQn;
	else if(TIMx == TIM5)  IRQn_reg = TIM5_IRQn;
	else if(TIMx == TIM9)  IRQn_reg = TIM1_BRK_TIM9_IRQn;
	else if(TIMx == TIM10) IRQn_reg = TIM1_UP_TIM10_IRQn;
	else if(TIMx == TIM11) IRQn_reg = TIM1_TRG_COM_TIM11_IRQn;
	return IRQn_reg;	
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11

**Return**

* the IRQ number of the timer

**Example code**

```c
uint32_t IRQn_reg = get_TIM_IRQn(TIMx);
```

### TIM_clock_enable()

Enables the timer clock.

```c
void TIM_clock_enable(TIM_TypeDef* TIMx){ 
	if(TIMx ==TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if(TIMx ==TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if(TIMx ==TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if(TIMx ==TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	else if(TIMx ==TIM5) RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	else if(TIMx ==TIM9) RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	else if(TIMx ==TIM10) RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	else if(TIMx ==TIM11) RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;	
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`), TIM1 to TIM5, TIM9 to TIM11

**Example code**

```c
TIM_clock_enable(TIMx);
```

---

## PWM

### Header File

`#include "ecPWM2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 10-26-2026
Language/ver     : C++ in VS Code

Description      : PWM Library. Distributed to Students for PreLAB Timer Interrupt & PWM
*          PWM library - exercise version.
*          Fill in every  "YOUR CODE GOES HERE"  and every  "____"  blank
*          in ecPWM2_student.c .  This header needs no editing.

/----------------------------------------------------------------*/

#ifndef __EC_PWM2_STUDENT_H
#define __EC_PWM2_STUDENT_H

#include "math.h"
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecTIM2.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/* PWM Output Mode : OCxM field in CCMRx (3 bits) */
#define EC_PWM_MODE1	0	// output active while CNT <  CCR  (default)
#define EC_PWM_MODE2	1	// output active while CNT >= CCR  (inverted)


///////////////////////////////////////////////////
/* 		        EXERCISE					     */
///////////////////////////////////////////////////

// Internal Helper function: for PWM Initialization
void PWM_init_config(PinName_t pinName, uint32_t usec);
// Duty ratio 0~1.0
void PWM_duty(PinName_t pinName, float duty);



///////////////////////////////////////////////////
/* 		GIVEN:  PWM Initialization                */
///////////////////////////////////////////////////

//  Low Frequency PWM initialization in msec. (below 1kHz)
// 	Default: 		50% duty ratio. PWM_mode1, Period in msec.
//  TIM2/TIM5 		(32-bit ARR) : msec 1 ~ 4,294,967
//  TIM1/TIM3/TIM4 	(16-bit ARR) : msec 1 ~ 6,553   
void PWM_init(PinName_t pinName, uint32_t msec);	// 1 to 6,553 msec (16-bit)

//  High-Frequency PWM initialization in usec (1kHz to 100 kHz)
// 	Default: 		50% duty ratio.  PWM_mode1, Period in usec.
//  TIM2/TIM5 		(32-bit ARR) : 	usec 1 ~ 4,294,967
//  TIM1/TIM3/TIM4 	(16-bit ARR) : 	usec 1 ~ 6,553   
void PWM_init_us(PinName_t pinName, uint32_t usec);	// 10 usec and up


///////////////////////////////////////////////////
/* 		GIVEN: DUTY RATIO SETUP                 */
///////////////////////////////////////////////////

// Set Pulse width in msec
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms);

// Set Pulse width in usec
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us);


////////////////////////////////////////////////////////////////
/* Internal Helper Functions - GIVEN. DO NOT MODIFY           */
////////////////////////////////////////////////////////////////

// Internal function for PWM output mode : EC_PWM_MODE1 or EC_PWM_MODE2
void PWM_mode_config(TIM_TypeDef *TIMx, int chN, uint32_t mode);
// Internal Helper function for PWM Pin Matching
void PWM_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_PWM2_STUDENT_H
```

### PWM_init()

Initializes the PWM output of the pin. The period is in msec.

```c
void PWM_init(PinName_t pinName, uint32_t msec){
	if(msec == 0) msec = 1;		// minimum 1 msec
	PWM_init_config(pinName, msec * 1000);		
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **msec**: PWM period in msec

**Example code**

```c
PWM_init(PWM_PIN, PWM_PERIOD_MS);
```

### PWM_init_us()

Initializes the PWM output of the pin. The period is in usec.

```c
void PWM_init_us(PinName_t pinName, uint32_t usec){	
	if(usec < 10) usec = 10;  // Minimum 10us (100kHz) 
	PWM_init_config(pinName, usec);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **usec**: PWM period in usec

**Example code**

```c
PWM_init_us(PWM_PIN, PWM_PERIOD_US);
```

### PWM_init_config()

Sets the pin and the timer for the PWM output.

```c
void PWM_init_config(PinName_t pinName, uint32_t usec){
// 0. Match TIMx from given Port_y and Pin_x
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);
	TIM_TypeDef *TIMx;
	int chN;
	PWM_pinmap(pinName, &TIMx, &chN);

// 1. Initialize GPIO port and pin as AF
	GPIO_init(pinName, AF);  

// 2. Configure GPIO AFR by Pin x num.
	//  AFR[0] holds pin 0~7, AFR[1] holds pin 8~15 : 4 bits per pin
		uint32_t afrIdx   = pin >> 3;				// same as (pin/8)
	uint32_t afrShift = 4 * (pin % 8);
	uint32_t afNum    = 0;

	//  AF1 for TIM1,TIM2     AF2 for TIM3,TIM4
	if((TIMx == TIM1)||(TIMx == TIM2))		afNum = 1;	// AF1
	else if(TIMx== TIM3 || TIMx == TIM4)	afNum = 2;	// AF2
	// You can add more  for TIM5 to TIM11, if necessary [YOUR CODE GOES HERE!!]		


	// Set AFR register for the pin
	port->AFR[afrIdx] &= ~(0xFUL << afrShift);	// 4 bits per pin	
	port->AFR[afrIdx] |= afNum << afrShift;


// 3. Initialize Timer : select CLK_CNT according to PWM period 
	//   TIM2/TIM5 			(32-bit ARR) : 1 < usec < 2^32 usec 	-> TIM_init_us() 
	//   TIM1/TIM3/TIM4    	(16-bit ARR) : 1 < usec <=65,536 usec 	-> TIM_init_us() 
	//                            			65 < msec <65,536 msec	-> TIM_init() 
	if((TIMx == TIM2) || (TIMx == TIM5) || (usec <= 65536)){
		TIM_init_us(TIMx, usec);					
	}
	else {
		uint32_t msec = usec / 1000;
		if(msec > 6553) msec = 6553;			// 16-bit ARR has limit of 6.5sec
		TIM_init(TIMx, msec);				// 65 < msec <65,536 msec	-> TIM_init() 	
	}

// 4. Configure Timer Output mode as PWM
	// Default: PWM Mode 1, active high, duty ratio = 50%
	PWM_mode_config(TIMx, chN, EC_PWM_MODE1);

// 5. Enable Timer Counter
	// For TIM1 ONLY
	if(TIMx == TIM1) TIMx->BDTR |= TIM_BDTR_MOE;					// Main output enable (MOE): 0 = Disable, 1 = Enable		
	// All Timer: First, Clear the counter and Clear UI Flag
	TIMx->EGR |= TIM_EGR_UG;					
	TIMx->SR   = ~TIM_SR_UIF;					
	// Enable timers
	TIMx->CR1  |= TIM_CR1_CEN;  	

}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **usec**: PWM period in usec

**Example code**

```c
PWM_init_config(pinName, usec);
```

### PWM_duty()

Sets the duty ratio of the PWM.

```c
void PWM_duty(PinName_t pinName, float duty){
// 0. Match TIMx from  Port and Pin
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);
	TIM_TypeDef *TIMx;
	int chN;
	PWM_pinmap(pinName, &TIMx, &chN);

// 1. Check the duty ratio range from 0.0 to 1.0
	if(duty < 0.0f) duty = 0.0f;		// if duty < 0.0f  -> duty = 0.0f;
	if(duty > 1.0f) duty = 1.0f;		// if duty > 1.0f  -> duty = 1.0f;

// 2. Duty ratio -> CCR counts.  Assume PWM mode 1 :
	uint32_t CCvalue = (TIMx->ARR + 1) * duty;	// (ARR+1) * duty
	
	if(chN == 1)      { TIMx->CCR1 = CCvalue; }	//set channel
	else if(chN == 2) { TIMx->CCR2 = CCvalue; }
	// REPEAT for CHn= 3, 4
	else if(chN == 3) { TIMx->CCR3 = CCvalue; }
	else if(chN == 4) { TIMx->CCR4 = CCvalue; }

}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **duty**: duty ratio, 0 to 1

**Example code**

```c
PWM_duty(PWM_PIN, duty);
```

### PWM_pulsewidth()

Sets the pulse width of the PWM in msec.

```c
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms){
// 0. Match TIMx from  Port and Pin 	
	GPIO_TypeDef *port;
	unsigned int pin;	
	ecPinmap(pinName, &port, &pin);	
	TIM_TypeDef *TIMx;
	int chN;		
	PWM_pinmap(pinName, &TIMx, &chN);

	float duty=0.0f;
	uint32_t f_cnt =0;

	
// 1. Counter clock : CK_CNT = EC_SYSCLK / (PSC+1)
	f_cnt = (uint32_t)EC_SYSCLK / (TIMx->PSC + 1);		// [Hz]

// 2. Convert Pulse_width [msec] -> duty ratio (0~1.0) 
	uint32_t counts = (uint32_t)(((uint64_t)f_cnt * pulse_width_ms) / 1000UL);
	duty = (float)counts / (float)(TIMx->ARR + 1);

// 3. Set duty ratio
	PWM_duty(pinName, duty);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **pulse_width_ms**: pulse width in msec

**Example code**

```c
PWM_pulsewidth(PWM_PIN, 1);
```

### PWM_pulsewidth_us()

Sets the pulse width of the PWM in usec.

```c
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us){
// 0. Match TIMx from  Port and Pin 	
	GPIO_TypeDef *port;
	unsigned int pin;	
	ecPinmap(pinName, &port, &pin);	
	TIM_TypeDef *TIMx;
	int chN;		
	PWM_pinmap(pinName, &TIMx, &chN);
	
	float duty=0.0f;
	
// 1. Counter clock : CK_CNT = EC_SYSCLK / (PSC+1)
	uint32_t f_cnt = (uint32_t)EC_SYSCLK / (TIMx->PSC + 1);		// [Hz]

// 2. Convert Pulse_width [usec] -> duty ratio (0~1.0) 
	// Exercise for Students
	uint32_t counts = (uint32_t)(((uint64_t)f_cnt * pulse_width_us) / 1000000UL);
	duty = (float)counts / (float)(TIMx->ARR + 1);

// 3. Set duty ratio
	PWM_duty(pinName, duty);
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **pulse_width_us**: pulse width in usec

**Example code**

```c
PWM_pulsewidth_us(PWM_PIN, pulse_us);
```

### PWM_mode_config()

Sets the PWM output mode of the channel.

```c
void PWM_mode_config(TIM_TypeDef *TIMx, int chN, uint32_t PWMmode){
	
	int mode=0x6; // default value for PWM mode 1
	if (PWMmode == EC_PWM_MODE2)	mode=0x7;  
	
	uint32_t ccVal = TIMx->ARR/2;  // default value  CC=ARR/2
	if(chN == 1){
		TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
		TIMx->CCMR1 |= ((mode << TIM_CCMR1_OC1M_Pos) & TIM_CCMR1_OC1M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch1
		TIMx->CCMR1	|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)
		TIMx->CCR1  = ccVal; 								// Output Compare Register for channel 1 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC1P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC1E;						// Enable output for ch1
	}
	else if(chN == 2){
		TIMx->CCMR1 &= ~TIM_CCMR1_OC2M;                     // Clear ouput compare mode bits for channel 2
		TIMx->CCMR1 |= ((mode << TIM_CCMR1_OC2M_Pos) & TIM_CCMR1_OC2M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch2
		TIMx->CCMR1	|= TIM_CCMR1_OC2PE;                     // Output 1 preload enable (make CCR1 value changable)	
		TIMx->CCR2  = ccVal; 								// Output Compare Register for channel 2 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC2P;                       // select output polarity: active high	
		TIMx->CCER |= TIM_CCER_CC2E;						// Enable output for ch2
	}
	else if(chN == 3){
		TIMx->CCMR2 &= ~TIM_CCMR2_OC3M;                     // Clear ouput compare mode bits for channel 3
		TIMx->CCMR2 |= ((mode << TIM_CCMR2_OC3M_Pos) & TIM_CCMR2_OC3M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch3
		TIMx->CCMR2	|= TIM_CCMR2_OC3PE;                     // Output 1 preload enable (make CCR1 value changable)	
		TIMx->CCR3  = ccVal; 								// Output Compare Register for channel 3 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC3P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC3E;						// Enable output for ch3
	}
	else if(chN == 4){
		TIMx->CCMR2 &= ~TIM_CCMR2_OC4M;                     // Clear ouput compare mode bits for channel 4
		TIMx->CCMR2 |= ((mode << TIM_CCMR2_OC4M_Pos) & TIM_CCMR2_OC4M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch4
		TIMx->CCMR2	|= TIM_CCMR2_OC4PE;                     // Output 1 preload enable (make CCR1 value changable)
		TIMx->CCR4  = ccVal;			 					// Output Compare Register for channel 4 (default duty ratio = 50%)				
		TIMx->CCER &= ~TIM_CCER_CC4P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC4E;						// Enable output for ch4
	}	
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`)
* **chN**: channel number, 1 to 4
* **PWMmode**: EC_PWM_MODE1(0), EC_PWM_MODE2(1)

**Example code**

```c
PWM_mode_config(TIMx, chN, EC_PWM_MODE1);
```

### PWM_pinmap()

Finds the timer and the channel of the pin.

```c
void PWM_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN)
{
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);

  	// Only  TIM1 to TIM4 are defined.
	// TIM5, 9 to 11 needs to be added, if necessary
  if(port == GPIOA) {
      switch(pin){
         case 0 : *TIMx = TIM2; *chN	= 1; break;
         case 1 : *TIMx = TIM2; *chN = 2; break;
         case 5 : *TIMx = TIM2; *chN = 1; break;
         case 6 : *TIMx = TIM3; *chN = 1; break;
         //case 7: TIMx = TIM1; *chN = 1N; break;
         case 8 : *TIMx = TIM1; *chN = 1; break;
         case 9 : *TIMx = TIM1; *chN = 2; break;
         case 10: *TIMx = TIM1; *chN = 3; break;
         case 15: *TIMx = TIM2; *chN = 1; break;
         default: break;
      }
   }
   else if(port == GPIOB) {
      switch(pin){
         //case 0: TIMx = TIM1; *chN = 2N; break;
         //case 1: TIMx = TIM1; *chN = 3N; break;
         case 3 : *TIMx = TIM2; *chN = 2; break;
         case 4 : *TIMx = TIM3; *chN = 1; break;
         case 5 : *TIMx = TIM3; *chN = 2; break;
         case 6 : *TIMx = TIM4; *chN = 1; break;
         case 7 : *TIMx = TIM4; *chN = 2; break;
         case 8 : *TIMx = TIM4; *chN = 3; break;
         case 9 : *TIMx = TIM4; *chN = 4; break;
         case 10: *TIMx = TIM2; *chN = 3; break;
         default: break;
      }
   }
   else if(port == GPIOC) {
      switch(pin){
         case 6 : *TIMx = TIM3; *chN = 1; break;
         case 7 : *TIMx = TIM3; *chN = 2; break;
         case 8 : *TIMx = TIM3; *chN = 3; break;
         case 9 : *TIMx = TIM3; *chN = 4; break;
         default: break;
      }
   }
	 // TIM5, 9, 11 needs to be added, if used.
	// [YOUR CODE GOES HERE!!] if necessary
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **TIMx**: the timer of the pin (output)
* **chN**: the channel number of the pin (output)

**Example code**

```c
PWM_pinmap(pinName, &TIMx, &chN);
```

---

## Input Capture

### Header File

`#include "ecICAP2.h"`

```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 05-03-2021
Modified         : 11-05-2026
Language/ver     : C++ in VS Code

Description      : Input Capture Library. Distributed to Students for Tutorial: Timer Input Capture
/----------------------------------------------------------------*/


#ifndef __EC_ICAP2_H
#define __EC_ICAP2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecTIM2.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Input Capture*/


// Edge Type
#define IC_RISE 0
#define IC_FALL 1
#define IC_BOTH 2

// Input Capture Number
#define IC_1 1
#define IC_2 2
#define IC_3 3
#define IC_4 4

// Input Capture Filter 
#define IC_FILTER_0		0		// no filter, transition sampled at fDTS
#define IC_FILTER_1		1		// N = 2 samples at fCK_INT
#define IC_FILTER_2		2		// N = 4 samples at fCK_INT
#define IC_FILTER_3		3		// N = 8 samples at fCK_INT


////////////////////////////////////////////////////////////////
/* Timer Input Capture  Initialization                        */
////////////////////////////////////////////////////////////////

// Default: 1 usec Tick Timer,  Assume TIn=ICn
void ICAP_init(PinName_t pinName, uint32_t edge_type);

// User-Defined IC channel for the pin, 1 usec tick
void ICAP_ICn_init(PinName_t pinName, uint32_t edge_type, uint32_t ICn);

// User-Defined tick in usec.  CALL THIS LAST
// usec range: 1 ~ 780 usec at 84 MHz (PSC is 16-bit).
void ICAP_tick(PinName_t pinName, uint32_t usec);

uint32_t ICAP_read(PinName_t pinName, uint32_t ICn);


//////////////////////////////////////////////
/* Timer Input CC Interrupt Configuration         */
//////////////////////////////////////////////
uint32_t is_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn);  // CCnum= 1~4
void clear_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn);


//////////////////////////////////////////////
/* Internal Functions                       */
//////////////////////////////////////////////
void ICAP_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);
void ICAP_filter(TIM_TypeDef *TIMx, uint32_t ICn, uint16_t filterOpt);
void ICAP_ICn_select(TIM_TypeDef *TIMx, uint32_t TIn, uint32_t ICn);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  // __EC_ICAP2_H
```

### ICAP_init()

Initializes the input capture of the pin.

```c
void ICAP_init(PinName_t pinName, uint32_t edge_type) {
    TIM_TypeDef *TIMx;
    int TIn;
    ICAP_pinmap(pinName, &TIMx, &TIn);

    ICAP_ICn_init(pinName, edge_type, TIn);		// ICn = TIn
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **edge_type**: IC_RISE(0), IC_FALL(1), IC_BOTH(2)

**Example code**

```c
ICAP_init(ECHO, IC_RISE);
```

### ICAP_ICn_init()

Initializes the input capture of the pin with the selected IC channel.

```c
void ICAP_ICn_init(PinName_t pinName, uint32_t edge_type, uint32_t ICn) {
// 0. Match Input Capture Port and Pin for TIMx
    GPIO_TypeDef *port;
    unsigned int pin;
    ecPinmap(pinName, &port, &pin);
    TIM_TypeDef *TIMx;
    int TIn;
    ICAP_pinmap(pinName, &TIMx, &TIn);

// GPIO configuration
// ---------------------------------------------------------------------
// 1. Initialize GPIO port and pin as AF
    GPIO_init(pinName, AF);         // AF=2
    GPIO_pupd(pinName,NO_PUPD);
    GPIO_ospeed(pinName, HIGH_SPEED);  // speed VHIGH=3

// 2. Configure GPIO AFR by Pin num.
    // AFR[0] holds pin 0~7, AFR[1] holds pin 8~15 
	uint32_t afrIdx   = pin >> 3;	// same as (pin/8)
	uint32_t afrShift = 4 * (pin % 8);
	uint32_t afNum    = 0;
	
	//  AF1 for TIM1,TIM2     AF2 for TIM3,TIM4
	if((TIMx == TIM1)||(TIMx == TIM2))		afNum = 1;	// AF1
	else if(TIMx== TIM3 || TIMx == TIM4 || TIMx == TIM5)	afNum = 2;	// AF2
    else if (TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11) afNum = 3;// AF3
	
	// Set AFR register for the pin
	port->AFR[afrIdx] &= ~(0xFUL << afrShift);	// 4 bits per pin
	port->AFR[afrIdx] |=  (afNum << afrShift);


// TIMER configuration (shared by all four channels)
// ---------------------------------------------------------------------
// 1. Timer clock, Update Interrupt and NVIC
    TIM_UI_init_us(TIMx, 1);        // TIMx Interrupt initialize at 1us=1MHz

// 2. Default tick = 1 usec, ARR at maximum
    ICAP_tick(pinName, 1);

// 3. Disable Counter during configuration
    TIMx->CR1 &= ~TIM_CR1_CEN;   


// Input Capture configuration (this channel only)
// ---------------------------------------------------------------------
// 1. Select Timer channel(TIx) for Input Capture channel(ICx)            
    ICAP_ICn_select(TIMx, TIn, ICn);

// 2. Filter Duration for THIS channel. Writing all four channels would
//    corrupt any channel of this timer that is used as an output: in CCMRx
//    the ICxF bits are the OCxM bits of an output channel.
    ICAP_filter(TIMx, ICn, IC_FILTER_3);    // N = 8 samples at fCK_INT
    
// 3. IC Prescaler (use default)

// 4. Activation Edge: CCyNP/CCyP        
    TIMx->CCER  &= ~(0b1010 << 4*(ICn - 1));  			// Clear CCnNP/CCnP bits
	switch(edge_type){
		case IC_RISE: TIMx->CCER &= ~(0b1010 << 4*(ICn - 1)); break; //rising:  00
		case IC_FALL: TIMx->CCER |= 0b0010 << 4*(ICn - 1); 	 break; //falling: 01
		case IC_BOTH: TIMx->CCER |= 0b1010 << 4*(ICn - 1); 	 break; //both:    11
	}

// 5.	Enable CCy Capture, Capture/Compare interrupt
    TIMx->CCER |= 1 << (4 * (ICn - 1));  // CCn(ICn) Capture Enable

// 6.	Enable Interrupt of CC(CCyIE), Update (UIE) per ICn
    TIMx->DIER |= 1 << ICn;      // Capture/Compare Interrupt Enable
    TIMx->DIER |= TIM_DIER_UIE;  // Update Interrupt enable

// 7.	Enable Counter
    TIMx->CR1 |= TIM_CR1_CEN;  // Counter enable
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **edge_type**: IC_RISE(0), IC_FALL(1), IC_BOTH(2)
* **ICn**: IC_1 to IC_4

**Example code**

```c
ICAP_ICn_init(ECHO, IC_FALL, IC_2);		//TI1 -> IC2, falling
```

### ICAP_tick()

Sets the counter tick of the input capture timer in usec.

```c
void ICAP_tick(PinName_t pinName, uint32_t usec) {
    // 0. Match Input Capture Port and Pin for TIMx
    TIM_TypeDef *TIMx;
    int CHn;
    ICAP_pinmap(pinName, &TIMx, &CHn);

    if(usec == 0)	usec = 1;			// usec is unsigned : 0 would give PSC = -1
    
    // 1. Prescaler for the requested tick. PSC is 16-bit, < 65536
    uint32_t presc = (uint32_t)(((uint64_t)usec * (uint32_t)EC_SYSCLK) / 1000000UL);
    if(presc < 1)		presc = 1;
    if(presc > 65536)	presc = 65536;			// clamp, PSC = presc - 1
    TIMx->PSC = presc - 1;

    // 2. Configure ARR to be Maximum 
    TIMx->ARR = 0xFFFF;  // Set auto reload register to maximum (count up to 65535)
    if((TIMx == TIM2)||(TIMx == TIM5))		TIMx->ARR = 0xFFFFFFFF;

    // 3. Clear the UIF 
    TIMx->EGR |= TIM_EGR_UG;
    TIMx->SR   = ~TIM_SR_UIF;
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **usec**: one tick in usec

**Example code**

```c
ICAP_tick(ECHO, uTick);
```

### ICAP_read()

Reads the captured value.

```c
uint32_t ICAP_read(PinName_t pinName, uint32_t ICn) {
    TIM_TypeDef *TIMx;
	int CHn;		
	ICAP_pinmap(pinName, &TIMx, &CHn);
    
    uint32_t capture_Value;

    if (ICn == 1)
        capture_Value = TIMx->CCR1;
    else if (ICn == 2)
        capture_Value = TIMx->CCR2;
    else if (ICn == 3)
        capture_Value = TIMx->CCR3;
    else
        capture_Value = TIMx->CCR4;

    return capture_Value;
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **ICn**: IC_1 to IC_4

**Return**

* the captured counter value

**Example code**

```c
cap_prev = ICAP_read(ECHO, IC_1);
```

### is_CCIF()

Checks the capture/compare interrupt flag.

```c
uint32_t is_CCIF(TIM_TypeDef *TIMx, uint32_t ICn) {
    return (TIMx->SR & (0x1UL <<  ICn)) != 0;
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`)
* **ICn**: IC_1 to IC_4

**Return**

* 1 if the flag is set, 0 if not

**Example code**

```c
if(is_CCIF(TIM4, IC_1)){					// IC1 : rising edge, SAME pin (TI1)
	cap_prev = ICAP_read(ECHO, IC_1);
	clear_CCIF(TIM4,IC_1);
}
```

### clear_CCIF()

Clears the capture/compare interrupt flag.

```c
void clear_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn) {
    // Clear the UIF  by writing
    TIMx->SR = ~(0x1UL << ICn);
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`)
* **ICn**: IC_1 to IC_4

**Example code**

```c
clear_CCIF(TIM4,IC_1);
```

### ICAP_pinmap()

Finds the timer and the channel of the pin.

```c
void ICAP_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN){
	 GPIO_TypeDef *port;
	 unsigned int pin;		
	 ecPinmap(pinName, &port, &pin);	
   
   if(port == GPIOA) {
      switch(pin){
         case 0 : *TIMx = TIM2; *chN = 1; break;
         case 1 : *TIMx = TIM2; *chN = 2; break;
         case 5 : *TIMx = TIM2; *chN = 1; break;
         case 6 : *TIMx = TIM3; *chN = 1; break;
         //case 7: *TIMx = TIM1; *chN = 1N; break;
         case 8 : *TIMx = TIM1; *chN = 1; break;
         case 9 : *TIMx = TIM1; *chN = 2; break;
         case 10: *TIMx = TIM1; *chN = 3; break;
         case 15: *TIMx = TIM2; *chN = 1; break;
         default: break;
      }         
   }
   else if(port == GPIOB) {
      switch(pin){
         //case 0: *TIMx = TIM1; *chN = 2N; break;
         //case 1: *TIMx = TIM1; *chN = 3N; break;
         case 3 : *TIMx = TIM2; *chN = 2; break;
         case 4 : *TIMx = TIM3; *chN = 1; break;
         case 5 : *TIMx = TIM3; *chN = 2; break;
         case 6 : *TIMx = TIM4; *chN = 1; break;
         case 7 : *TIMx = TIM4; *chN = 2; break;
         case 8 : *TIMx = TIM4; *chN = 3; break;
         case 9 : *TIMx = TIM4; *chN = 4; break;
         case 10: *TIMx = TIM2; *chN = 3; break;
         
         default: break;
      }
   }
   else if(port == GPIOC) {
      switch(pin){
         case 6 : *TIMx = TIM3; *chN = 1; break;
         case 7 : *TIMx = TIM3; *chN = 2; break;
         case 8 : *TIMx = TIM3; *chN = 3; break;
         case 9 : *TIMx = TIM3; *chN = 4; break;
         
         default: break;
      }
   }
}
```

**Parameters**

* **pinName**: pin name (`PinName_t`)
* **TIMx**: the timer of the pin (output)
* **chN**: the channel number of the pin (output)

**Example code**

```c
ICAP_pinmap(pinName, &TIMx, &TIn);
```

### ICAP_filter()

Sets the input capture filter.

```c
void ICAP_filter(TIM_TypeDef *TIMx, uint32_t ICn, uint16_t filterOpt)
{
	// 4 bits per channel: ICnF at bit 4 (ch 1, 3) and bit 12 (ch 2, 4)
	uint32_t shift = (ICn % 2) ? 4 : 12;			// odd channel -> 4, even -> 12

	if(ICn == 1 || ICn == 2){
		TIMx->CCMR1 &= ~(0xFUL  << shift);
		TIMx->CCMR1 |=  (filterOpt << shift);
	}
	else{
		TIMx->CCMR2 &= ~(0xFUL  << shift);
		TIMx->CCMR2 |=  (filterOpt << shift);
	}
}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`)
* **ICn**: IC_1 to IC_4
* **filterOpt**: IC_FILTER_0 to IC_FILTER_3

**Example code**

```c
ICAP_filter(TIMx, ICn, IC_FILTER_3);    // N = 8 samples at fCK_INT
```

### ICAP_ICn_select()

Connects the timer input to the IC channel.

```c
void ICAP_ICn_select(TIM_TypeDef *TIMx, uint32_t TIn, uint32_t ICn){
// 2. Configure  IC number(user selected) with given IC pin(TIMx_CHn)
	switch(ICn){
			case 1:
					TIMx->CCMR1 &= ~TIM_CCMR1_CC1S;						//reset   CC1S
					if (ICn==TIn) TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_0;   //01<<0   CC1S    Tx_Ch1=IC1
					else TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_1;      		//10<<0   CC1S    Tx_Ch2=IC1
					break;
			case 2:
					TIMx->CCMR1 &= ~TIM_CCMR1_CC2S;						//reset   CC2S
					if (ICn==TIn) TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_0;   //01<<0   CC2S    Tx_Ch2=IC2
					else TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_1;      		//10<<0   CC2S    Tx_Ch1=IC2
					break;
			case 3:
					TIMx->CCMR2 &= ~TIM_CCMR2_CC3S;						//reset   CC3S
					if (ICn==TIn) TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_0;   //01<<0   CC3S    Tx_Ch3=IC3
					else TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_1;      		//10<<0   CC3S    Tx_Ch4=IC3
					break;
			case 4:
					TIMx->CCMR2 &= ~TIM_CCMR2_CC4S;						//reset   CC4S
					if (ICn==TIn) TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_0;   //01<<0   CC4S    Tx_Ch4=IC4
					else TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_1;      		//10<<0   CC4S    Tx_Ch3=IC4
					break;
			default: break;
		}

}
```

**Parameters**

* **TIMx**: timer (`TIM_TypeDef *`)
* **TIn**: timer input number
* **ICn**: IC_1 to IC_4

**Example code**

```c
ICAP_ICn_select(TIMx, TIn, ICn);
```

---

## Custom Initialization

### Header File

`#include "ecSTM32F4v2.h"`

### MCU_init()

Calls the commonly used default initialization.

```c
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
```

**Parameters**

* None

**Example code**

```c
MCU_init();                     // System Clock = 84MHz, SysTick 1msec
```

---
