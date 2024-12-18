#include "stm32l476xx.h"
#include "SysClock.h"

void assign(uint32_t t) {
	GPIOC->ODR &= ~((0x1F) | (0x1F << 8)); //clear PC 0-4 and PC 8-12
	GPIOC->ODR |= (t & 0x1F); //assign PC 0-4
	GPIOC->ODR |= ((t>>5) &0x1F) << 8; //assign PC 8-12
}

void delay (int milliseconds) {
	int i;
	for (i = 0; i < milliseconds; i++);
}

void forwardBackwardSequence() {
	uint8_t d = 1; // 1 is forward, 0 is backward
	int pos = 0; //start from PC0
	int max_pos = 9; //max position for LEDs
	
	while(1) {
		int i;
		for (i=0; i < 1000; i++) {
			uint32_t t = 0; //clear all LED positions
			            // Set new LED positions based on pos
			if (pos >= 0) {
					t |= (1 << pos);
					t |= (1 << (pos + 1));
					t |= (1 << (pos + 2));
					t |= (1 << (pos + 3)); // Add one more LED
			} 
			else if (pos == 5) {
					t |= (1 << pos);
					t |= (1 << (pos + 1));
					t |= (1 << (pos + 2));
					t |= (1 << (pos + 3)); // Add one more LED
			} 
			else if (pos == 7) {
					t |= (1 << pos);
					t |= (1 << (pos + 1));
					t |= (1 << (pos + 2)); // Add one more LED
			}
			else if (pos == 8) {
					t |= (1 << pos);
					t |= (1 << (pos + 1)); // Add one more LED
			}
			else if (pos == 9) {
					t |= (1 << pos); // Only one LED at pos = 9
			}
            assign(t);
            delay(10);
        }

        delay(200 * 5600); // Move the position of the lit LEDs forward or backward*/

        if (d) {
            pos++; // Move forward
            if (pos == max_pos) { // If we reach the maximum position, change direction
                d = 0;
                delay(10); // Add a small delay to smoothly transition without pause
            }
        } else {
            pos--; // Move backward
            if (pos == 0) { // If we reach the minimum position, change direction
                d = 1;
                delay(10); // Add a small delay to smoothly transition without pause
            }
				}
		}
}			
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
	
	while (1) {
		forwardBackwardSequence();
	}
}
