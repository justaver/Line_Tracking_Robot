#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"


void senor_Pin_Init(){
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->APB1ENR1 = RCC_APB1ENR1_TIM4EN;
		
	GPIOB->AFR[0]&=~0x0F000000; //Clearing Pin 6 (port B) AFR (low)
	GPIOB->AFR[0]|=0x02000000; //Setting Pin 6 (port B) AFR (low) to TIM4_CH1(0010)

	

	
	
}

void timer_config(){
	//Extra Credit
	TIM4->PSC = 15;//16MHZ clock down to 1MhZ
	
	TIM4->ARR = 0xFFFF; //Setting AAR register to the maximumum(16-bit)
	
	TIM4->CCMR1 &= ~0x3; //Clearing the CCS1 value (in CCMR1 register)
	TIM4->CCMR1 &= ~0x1; //Setting the the CCS1 value to input (01)
	TIM4->CCMR1 &= ~0xF0; //setting the IC1F (in register CCMR1 to 0);it has 4 bits
	
	TIM4->CCER &= ~0xA; //Seeting cc1p and ccnp to 11 (in CCER register)
	TIM4->CCER &= 0xA;
	
}

void MOODDARR(void){
	 GPIOA->MODER &= ~0x00000C00; 
	  GPIOA->MODER |= 0x00000400;
	
		
	//MODER Resigeter (Mode: output: 01): Port C: Pin 0
	GPIOC->MODER &= ~0x3;//clearing the last two bits 
	GPIOC->MODER |= 0x1;// setting the last two bits to 01
	
	//ODR Register Mode: Mode: output (on): 1: : Port C: Pin 0
	GPIOC->ODR &= ~0x1; //clearng the first bit
	GPIOC->ODR |= 0x1; // setting the first bit to 1
	
	delay(10000);
	
	//MODER Resigeter (Mode: input: 00): Port C: Pin 0
	GPIOC->MODER &= ~0x3;//clearing the last two bits 
	
}