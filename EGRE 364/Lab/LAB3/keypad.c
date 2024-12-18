#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"

void keypad_Pin_Init(){
	 //Activating clock and ports
	//System_Clock_Init();
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; 
	
	//Keypad Row pins (outputs:01)
	GPIOC->MODER &= ~0xFF;
	GPIOC->MODER |=  0x55;
	
	//Keyoad Coulumn pinns (inputs:00)
	GPIOC->MODER &= ~0x03F00300;
	
	
}

  
	
	