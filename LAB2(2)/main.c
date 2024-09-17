#include "stm32l476xx.h"
#include "SysClock.h"

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
//#define LED_PIN    5
//#define BUTTON_PIN 13

int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz
	// Enable the clock to GPIO Port C	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;   
	
	//MODER REGISTER
	GPIOC->MODER&= ~0x000003FF; 
	GPIOC->MODER&= GPIOC->MODER |= 0x00000155;
	//OTYPER REGISTER
	GPIOC->OTYPER &= ~0x0000001F;
	GPIOC->OTYPER |= 0x00000000;
	//PUPDR REGISTER
	GPIOC->PUPDR &= ~0x000003FF;
	GPIOC->PUPDR |= ~0x00000000;
	
	//MODER REGISTER
	GPIOC->MODER &= ~0x03FF0000;  
	GPIOC->MODER |= 0x01550000;    

	//MODER REGISTER
	GPIOC->OTYPER &= ~ 0x001F0000;
	GPIOC->OTYPER |= 0x00000000;

	
	GPIOC->PUPDR &= ~0x03FF0000;
	GPIOC->PUPDR |= ~0x00000000;
	
	


	
	
}
