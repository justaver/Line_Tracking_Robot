#include "stm32l476xx.h"
#include "SysClock.h"

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5
#define BUTTON_PIN 13

int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	  // Enable the clock to GPIO Port B	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   
	
	// MODE: 00: Input mode, 01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
  GPIOA->MODER &= ~(0x03<<(2*5)) ;   // Clear bit 13 and bit 12 for Port B
  GPIOA->MODER |= (1<<10);
		
	GPIOA->ODR |= GPIO_ODR_ODR_5;
  // Dead loop & program hangs here
	
	while(1);
}
