#include "stm32l476xx.h"
#include "SysClock.h"

void motor_control_1(){
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Enable clock for GPIOA
	// Set PA6 (TIM3_CH1), PA7 (TIM3_CH2) to Alternate Function (AF2)
		GPIOA->MODER &= ~(0xF << (6 * 2));  // Clear MODER for PA6 and PA7
    GPIOA->MODER |= (0xA << (6 * 2));   // Set MODER to Alternate Function (10) for PA6 and PA7
    GPIOA->AFR[0] &= ~(0xFF << (6 * 4)); // Clear AFRL for PA6 and PA7
    GPIOA->AFR[0] |= (0x22 << (6 * 4));  // Set AF2 (TIM3) for PA6 and PA7
}

void motor_control_2(){
	    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	 // Set PB0 (TIM3_CH3), PB1 (TIM3_CH4) to Alternate Function (AF2)
    GPIOB->MODER &= ~(0xF << (0 * 2));  // Clear MODER for PB0 and PB1
    GPIOB->MODER |= (0xA << (0 * 2));   // Set MODER to Alternate Function (10) for PB0 and PB1
    GPIOB->AFR[0] &= ~(0xFF << (0 * 4)); // Clear AFRL for PB0 and PB1
    GPIOB->AFR[0] |= (0x22 << (0 * 4));  // Set AF2 (TIM3) for PB0 and PB1
}

void Motor_SetSpeed(int motor, int speed) {
    // Clamp speed to range -100 to 100
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;

    // Calculate duty cycle
    int duty_cycle;
		if (speed < 0) {
    duty_cycle = -speed; // Take the negative of speed if it's less than 0
		} 
		else {
    duty_cycle = speed;  // Otherwise, keep it as is
		}
		
    int CCR_value = (duty_cycle * TIM3->ARR) / 100; // Map to ARR

    // Set direction and speed
    if (motor == 1) {
        if (speed >= 0) {
            TIM3->CCR1 = CCR_value; // Forward on CH1
            TIM3->CCR2 = 0;         // Stop CH2
        } else {
            TIM3->CCR1 = 0;         // Stop CH1
            TIM3->CCR2 = CCR_value; // Reverse on CH2
        }
    } else if (motor == 2) {
        if (speed >= 0) {
            TIM3->CCR3 = CCR_value; // Forward on CH3
            TIM3->CCR4 = 0;         // Stop CH4
        } else {
            TIM3->CCR3 = 0;         // Stop CH3
            TIM3->CCR4 = CCR_value; // Reverse on CH4
        }
    }
}

int main(void){
		System_Clock_Init(); // Switch System Clock = 80 MHz
		motor_control_1();
		motor_control_2();
		
	
	 // Enable TIM3 clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

    // Set prescaler and auto-reload for 1 kHz PWM frequency
    TIM3->PSC = 1599;              
    TIM3->ARR = 999;            

    // Configure PWM Mode 1 for all channels
    TIM3->CCMR1 &= ~((0x7 << 4) | (0x7 << 12)); // Clear OC1M and OC2M
    TIM3->CCMR1 |= ((6 << 4) | (6 << 12));      // Set PWM Mode 1 for CH1 and CH2
    TIM3->CCMR2 &= ~((0x7 << 4) | (0x7 << 12)); // Clear OC3M and OC4M
    TIM3->CCMR2 |= ((6 << 4) | (6 << 12));      // Set PWM Mode 1 for CH3 and CH4

    // Enable preload for all channels
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;

    // Enable TIM3 channels
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

    // Enable TIM3 counter
    TIM3->CR1 |= TIM_CR1_CEN;
		
	while(1){
			 Motor_SetSpeed(1, 100);  // Motor 1: Full speed forward
        Motor_SetSpeed(2, 100);  // Motor 2: Half speed reverse
        for (volatile int i = 0; i < 1000000; i++); // Delay

        // Example: Stop both motors
       // Motor_SetSpeed(1, 0);    // Motor 1: Stop
       // Motor_SetSpeed(2, 0);    // Motor 2: Stop
        for (volatile int i = 0; i < 1000000; i++); // Delay
		}
}


//int duty_cycle = (speed < 0) ? -speed : speed; //learning how to use the tenary operator might implement eventually

