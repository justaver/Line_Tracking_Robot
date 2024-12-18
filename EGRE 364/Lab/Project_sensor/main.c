#include "stm32l476xx.h"
#include "SysClock.h"
#include <stdio.h>




void delay(int a){
	for (int i = 0; i<= a; i++){}
}

void sensor_algorithim1(int threshold_A){
	//This algorithim gets the the threshold value
	int counter;
	//MODER Resigeter (Mode: output: 01): Port C: Pin 0
	GPIOC->MODER &= ~0x3;//clearing the last two bits 
	GPIOC->MODER |= 0x1;// setting the last two bits to 01
	//ODR Register Mode: Mode: output (on): 1: : Port C: Pin 0
	GPIOC->ODR &= ~0x1; //clearng the first bit
	GPIOC->ODR |= 0x1; // setting the first bit to 1
	delay(5000);
	//MODER Resigeter (Mode: input: 00): Port C: Pin 0
	GPIOC->MODER &= ~0x3;//clearing the last two bits 
	//GPIOA->ODR |= GPIO_ODR_ODR_5;
		counter = 0;
		while((GPIOC->IDR & (1UL << 0)) == 1){
			counter ++;
		}	//2nd WHILE LOOP END 
	    if(counter >= threshold_A) {
        GPIOA->ODR |= (1UL << 5);  // Turn on LED if a black surface is detected
    }
		else{
			 GPIOA->ODR &= ~(1UL << 5);
		}
}

void sensor_algorithim2(int threshold_A){
	//This algorithim gets the the threshold value
	int counter;
	//MODER Resigeter (Mode: output: 01): Port C: Pin 0
	GPIOC->MODER &= ~0xC;//clearing the last two bits 
	GPIOC->MODER |= 0x4;// setting the last two bits to 01
	//ODR Register Mode: Mode: output (on): 1: : Port C: Pin 0
	GPIOC->ODR &= ~0x2; //clearng the first bit
	GPIOC->ODR |= 0x2; // setting the first bit to 1
	delay(5000);
	//MODER Resigeter (Mode: input: 00): Port C: Pin 0
	GPIOC->MODER &= ~0xC;//clearing the last two bits 
	//GPIOA->ODR |= GPIO_ODR_ODR_5;
		counter = 0;
		while((GPIOC->IDR & (1UL << 1)) == 2){
			counter ++;
		}
	    if(counter >= threshold_A) {
        GPIOA->ODR |= (1UL << 5);  // Turn on LED if a black surface is detected
    }
		else{
			 GPIOA->ODR &= ~(1UL << 5);
		}
}
void sensor_algorithim3(int threshold_A){
	//This algorithim gets the the threshold value
	int counter;
	//MODER Resigeter (Mode: output: 01): Port C: Pin 0
	GPIOC->MODER &= ~0x30;//clearing the last two bits 
	GPIOC->MODER |= 0x10;// setting the last two bits to 01
	//ODR Register Mode: Mode: output (on): 1: : Port C: Pin 0
	GPIOC->ODR &= ~0x4; //clearng the first bit
	GPIOC->ODR |= 0x4; // setting the first bit to 1
	delay(5000);
	//MODER Resigeter (Mode: input: 00): Port C: Pin 0
	GPIOC->MODER &= ~0x30;//clearing the last two bits 
	//GPIOA->ODR |= GPIO_ODR_ODR_5;
		counter = 0;
		while((GPIOC->IDR & (1UL << 2)) == 4){
			counter ++;
		}	//2nd WHILE LOOP END 
	    if(counter >= threshold_A) {
        GPIOA->ODR |= (1UL << 5);  // Turn on LED if a black surface is detected
    }
		else{
			 GPIOA->ODR &= ~(1UL << 5);
		}
}
void sensor_algorithim4(int threshold_A){
	//This algorithim gets the the threshold value
	int counter;
	//MODER Resigeter (Mode: output: 01): Port C: Pin 0
	GPIOC->MODER &= ~0xC0;//clearing the last two bits 
	GPIOC->MODER |= 0x40;// setting the last two bits to 01
	//ODR Register Mode: Mode: output (on): 1: : Port C: Pin 0
	GPIOC->ODR &= ~0x8; //clearng the first bit
	GPIOC->ODR |= 0x8; // setting the first bit to 1
	delay(5000);
	//MODER Resigeter (Mode: input: 00): Port C: Pin 0
	GPIOC->MODER &= ~0xC0;//clearing the last two bits 
	//GPIOA->ODR |= GPIO_ODR_ODR_5;
		counter = 0;
		while((GPIOC->IDR & (1UL << 3)) == 8){
			counter ++;
		}	//2nd WHILE LOOP END 
	    if(counter >= threshold_A) {
        GPIOA->ODR |= (1UL << 5);  // Turn on LED if a black surface is detected
    }
		else{
			 GPIOA->ODR &= ~(1UL << 5);
		}
}
int main(void){
	int threshold_A = 30000;
  int threshold_B = 3000;
	
		
  System_Clock_Init(); // Switch System Clock = 80 MHz
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enabling clock A
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //Enabling clock C
	
	//these jaunts for the light. Don't delete.
	  GPIOA->MODER &= ~0x00000C00; 
	  GPIOA->MODER |= 0x00000400;
		
	
	//This algorithim gets the the threshold value
	while(1){
		sensor_algorithim1(threshold_A);
		//sensor_algorithim2(threshold_A);
		//sensor_algorithim3(threshold_A);
		//sensor_algorithim4(threshold_A);
	
}
		
	
	
}//MAIN END
