#include <string.h>
#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"
#include "I2C.h"
#include "ssd1306.h"
#include "keypad.h"


uint8_t Data_Receive[6];
uint8_t Data_Send[6];


void I2C_GPIO_init(void);

void wait(int a){
	for(int x = 0; x <= a; x++);
}

unsigned char keypad_scan (void){
	unsigned char key_map [4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'}
	}; 
	unsigned char row, col, ColumnPressed;
	unsigned char key = 0xFF;
	uint32_t inputMask, outputMask;
	int rows[] = {0, 1, 2, 3};
	int cols[] = {4, 10, 11, 12};
	
	for (col = 0;col < 4; col++) inputMask |= 1<<cols[col];	
	for (col = 0;row < 4; row++) outputMask |= 1<<rows[row];
	
	GPIOC->ODR &= ~outputMask;
	wait(999);
	if((GPIOC->IDR & inputMask) == inputMask) return 0xFF;
	//Column Identifier	
	for(col = 0; col < 4; col++){
		if ((GPIOC->IDR & (1<<cols[col])) == 0) 
			ColumnPressed = col;
	}
	//Row identifier
	for(row = 0; row < 4; row++){
		GPIOC->ODR |= outputMask;
		GPIOC->ODR &= ~(1<<rows[row]);
		wait(999);
	
		if ((GPIOC->IDR & (1<<cols[ColumnPressed])) == 0) {
			key = key_map[row][ColumnPressed];
		}
	}

	
	return key;
}





	
int main(void){
	
	
	unsigned char key,previous_key;
	unsigned char len = 0;
	char str[50];
	volatile int i;
	int count = 0;
	char message[64] = "";
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	I2C_GPIO_init();
	I2C_Initialization(I2C1);

	ssd1306_Init();
	ssd1306_Fill(White);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString(message, Font_11x18, Black);		
	ssd1306_UpdateScreen();
	keypad_Pin_Init();
	
	while(1){

		key = keypad_scan();
		
		switch (key){
			case 0xFF:
			break;
		default:
			//putting the key into a string, ssd1306_WriteString(str, Font_11x18, Black); is like the prinf statment, it displays the message(our str the message) the message takes an "arry" of values" not just an integer.
          str[len] = key;
					len++;
					wait(1600000);
		// seting the length of str to 8, so the oled will display up to 7 character
		    if(len>=8){
					len=0;
					// When str reaches 7 charaters, it will got 0. so it will clear the oled numbers.
					for (int i = 0; i < 10; i++) {
						str[i] = 0xFF;
					}
        }
				//olded screan ouput messages
		    ssd1306_Fill(White);
        ssd1306_SetCursor(2,0);
        ssd1306_WriteString(str, Font_11x18, Black);        
        ssd1306_UpdateScreen();
				
			}		
	

		
		
	}
}
		 
	
