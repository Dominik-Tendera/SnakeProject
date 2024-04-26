#include "matrix.h"
#include <avr/io.h>

matrix_state_t matrix[MATRIX_ROW_COUNT][MATRIX_COL_COUNT]; 

void matrix_init(void) {
    // Configure col registers as output
    DDRC  = 0xFF;
    PORTC = 0x00;
    // Configure row registers as output and set to low
    DDRD  = 0xFF;
    PORTD = 0x00;
}

void matrix_set(uint8_t row, uint8_t col, matrix_state_t val) {
    matrix[row][col] = val;
}

void matrix_set_row(uint8_t row, matrix_state_t val) {
    for (uint8_t col = 0; col < MATRIX_COL_COUNT; col++) {
		matrix[row][col] = val;
	}
}

void matrix_set_col(uint8_t col, matrix_state_t val) {
    for (uint8_t row = 0; row < MATRIX_ROW_COUNT; row++) {
        matrix[row][col] = val;
    }
}

void matrix_set_all(matrix_state_t val) {
    for (uint8_t row = 0; row < MATRIX_ROW_COUNT; row++) {
        for (uint8_t col = 0; col < MATRIX_COL_COUNT; col++) {
            matrix[row][col] = val;
        }
    }
}

void matrix_update(void) {
    static uint8_t loc_row = 0;			//static oznacza �e tworzymy zmienn� ktora zachowuje si� jak globalna i ostatnia warto�� zmiennej jest zapami�tania pomimo sko�czenia si� funkcji w kt�rej jest zawarta 
    static uint8_t loc_col = 0;
	
    matrix_state_t val = matrix[loc_row][loc_col];

    // Write led
    if (val) {
		PORTC = ~(1 << loc_col);  
        PORTD =  (1 << loc_row);
    } else {
        PORTD = 0;
        PORTC = 0;
    }

    // Move to the next led in a loc_row
    // Loop to the next loc_col if we reach the end
    if (++loc_col >= MATRIX_COL_COUNT) {
        loc_col = 0;
        if (++loc_row >= MATRIX_ROW_COUNT) {
            loc_row = 0;
        }
    }
}
