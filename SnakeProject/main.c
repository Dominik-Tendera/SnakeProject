#include <stdint.h>
#include "matrix.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdlib.h>

/*	---------------------------------------------------------------------------------
 *	This is the 2022 student project on Atmega328pb   
 * 	Snake Game controled by 5 buttons pulling to ground 
 * 	Display of size 7 rows 5 columns each led controled by setting values of correct row and a column
 *  ----------------------------------------------------------------------------------
*/


uint8_t cont_state = 9;								//ustawienia pocz�tkowe gry 
uint8_t g_row = 3, g_col = 2;
uint8_t length = 1;
uint8_t food_row = 5;
uint8_t food_col = 3;

//Interrupt												//B0 - K1(ta z prawej) B1 - K2  B2 - K3 || B3 - W1 (g�rny wiersz)  B4 - W2  B5 - W3
ISR(PCINT0_vect) 
{	
	PCMSK0 = 0;											//Disable pcint interrupts on portc

	uint8_t local_state = 0;
	
	DDRB = 0b00011000;									//Set rows as outputs and columns as inputs
	PORTB = 0b00000111;
	local_state = PINB & 0b00000111;					//reads which column
			
	DDRB = 0b00000111;									//Set rows as inputs and columns as outputs
	PORTB = 0b00011000;									//Set rows to high (pull ups) and columns to low
	local_state |= PINB & 0b00011000;					//reads which row and combines with columd record
														
														// left = 20 |  right = 17 | down = 18 | up = 10 | reset = 9 | animation = 12
														//Warunek uniemo�liwiaj�cy przekazanie b��dnego wyniku po puszczeniu przycisku
	if(local_state == 20 || local_state == 17 || local_state == 18 || local_state == 10 || local_state == 9 || local_state == 12){
		cont_state = local_state;
	}
	
	PCMSK0 = (1<<PCINT3)|(1<<PCINT4)|(1<<PCINT5);		//Restore rows as pcint interrupt triggers
	
}

void reset(){
	matrix_set_all(OFF);
	matrix_set(3,2,ON);
	g_row = 3;
	g_col = 2;
	cont_state = 9;
	length = 2;
}
			
void movement_conditioning(matrix_state_t value){
	if(matrix[g_row][g_col]==OFF){
		matrix_set(g_row,g_col,value);
	}
	else if(matrix[g_row][g_col]==FOOD){			//warunek zwi�kszaj�cy d�ugo�� i losuj�cy nowe po�o�enie jedzenia na macierzy
		matrix_set(g_row,g_col,value);
		length++;
		do{
			food_row = rand() % 7;
			food_col = rand() % 5;
		}
		while(matrix[food_row][food_col] != OFF);
	}
	else{
		reset();									//warunek ko�cz�cy gr�
	}
}			
			
void snake_movement(){
	if(cont_state == 9){			//reset
		reset();
	}
	else if(cont_state==17){		//right
		g_col++;
		if(g_col>4){								
			g_col = 0;
		}
		movement_conditioning(RIGHT);
	}
	else if(cont_state==18){		//down
		g_row++;
		if(g_row>6){
			g_row = 0;
		}
		movement_conditioning(DOWN);
	}
	else if(cont_state==10){		//up
		if(g_row==0){
			g_row = 7;
		}
		g_row--;
		movement_conditioning(UP);
	}
	else if(cont_state==20){		//left
		if(g_col==0){
			g_col = 5;
		}
		g_col--;
		movement_conditioning(LEFT);
	}	
	
	matrix_set(food_row, food_col, FOOD);					
}

				
void snake_tail(){
	uint8_t loc_row = g_row;
	uint8_t loc_col = g_col;
	
	for(uint8_t i = length; i <= length; i--){		//P�tla wy��czaj�ca diod� za ogonem w�a w zale�no�ci od parametru length
		if(matrix[loc_row][loc_col] == RIGHT){
			if(loc_col==0){
				loc_col = 5;
			}
			loc_col--;
		}
		else if(matrix[loc_row][loc_col] == DOWN){
			if(loc_row==0){
				loc_row = 7;
			}
			loc_row--;
		}
		else if(matrix[loc_row][loc_col] == UP){
			loc_row++;
			if(loc_row>6){
				loc_row = 0;
			}
		}
		else if(matrix[loc_row][loc_col] == LEFT){
			loc_col++;
			if(loc_col>4){
				loc_col = 0;
			}
		}
		if(i==0){
			matrix_set(loc_row,loc_col,OFF);
		}
		
		
	}
}
			
			
void main() {
	matrix_init();
	PCICR = (1<<PCIE0);
	PCMSK0 = (1<<PCINT3)|(1<<PCINT4)|(1<<PCINT5);	//Ustawienie przerwania wywo�ywanego zmian� na 3 pinach B
	sei();
	
	// Main loop
	uint16_t prescaler_game_update = 0;
	while (1) {
		if(prescaler_game_update++ > 1400) {
			prescaler_game_update = 0;
			matrix_init();							//na czas dokonywania zmian w macierzy zgaszenie wy�wietlacza
			snake_movement();
			snake_tail();
		}
		// Updates one LED at a time
		matrix_update();
		_delay_us(100);
	}
}			
			
			
		
		
		
			
			
			
			/**KOD Z ANIMACJ�
			else if(cont_state == 12){	
				static uint8_t led_state = 0;
				led_state = !led_state;
				matrix_set_all(OFF);
				
				if(led_state) {
					matrix_set_all(ON);
					matrix_set_col(2, OFF);
				} else {
					matrix_set_all(OFF);
					matrix_set_col(2, ON);
				}
			}**/
			
			
			
			/**
			SPRAWDZENIE DZIA�ANIA KONTROLERA
			else if(cont_state==17){	//right
				matrix_set(1,2,ON);
			}
			else if(cont_state==18){	//down
				matrix_set(1,1,ON);
			}
			else if(cont_state==10){	//up
				
					matrix_set(0,1,ON);
			}
			**/