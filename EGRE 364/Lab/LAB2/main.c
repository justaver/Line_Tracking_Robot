#include "stm32l476xx.h"
#include "SysClock.h"


#define LED_PIN    5
#define BUTTON_PIN 13

int main(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
// PA.5  <--> Green LED
	
// Enable the clock to GPIO Port A nd C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;   
	
	  GPIOA->MODER &= ~0x00000C00; 
	  GPIOA->MODER |= 0x00000400;  
	  //GPIOA->MODER &= ~(3UL << (5*2));
	  //GPIOA->MODER |= (1UL << (5*2));
	
	  GPIOA->OTYPER &= ~0x00000020;
	  GPIOA->OTYPER |= 0x00000000;
	  //GPIOA->OTYPER &= ~(1UL << 5);
	
	  GPIOA->PUPDR &= ~0x00000C00;
	  GPIOA->PUPDR |= 0x00000000;
	  //GPIOA->PUPDR &= ~(3UL <<5*2);
	
// PC.13 <--> Blue user button
	 
	
	// MODE: 00: Input mode, 01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
    GPIOC->MODER &= ~0x0C000000; 
    GPIOC->MODER |= 0x00000000;
	//GPIOC->MODER &= ~(3UL << 13*2);
		
	
	   GPIOC->PUPDR &= ~0x0C000000;
	   GPIOC->PUPDR |= 0x00000000;
	//GPIOC->PUPDR &= ~(3UL << 13*2);
	
	//GPIOA->ODR |= GPIO_ODR_ODR_5;
	//GPIOA->ODR |= (1 << 5);
	
	//Toggle
	
	while(1){
		
		if((GPIOC->IDR & (1UL << 13)) == 0){
			GPIOA->ODR ^= (1 << 5);
			while((GPIOC->IDR & (1UL << 13))==0);
				
		}
		else{
			continue; //this is not needed, testing purpses...don't worry about it. )
		}
			
	}

}