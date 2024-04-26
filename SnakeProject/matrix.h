#pragma once
#include <stdint.h>		//biblioteka kt�ra dodaje typ zmiennie uint8_t (8bitowy unsingned int) to samo co unsigned char

#define MATRIX_ROW_COUNT 7   //Dodanie sta�ej warto�ci, kompilator zamienia wszystkie wyst�pnie w kodzie na matrix-row... na 7
#define MATRIX_COL_COUNT 5

typedef enum {			//definiowanie typu zmiennej matrix_state_t zmienna mo�e przyjmowa� dwie warto��i Matrix off ON kt�re sa r�wnowa�ne z 0 i 1 
	OFF = 0,		// polepsza to czytelno�c kodu poniewa� wpisujmey zmiennie typu OFF kt�ra nie jest losow pojawiaj�c� si� liczb� w kodzie 
	ON  = 1,		// jest to spos�b na nazwanie liczb w jaki� znacz�cy spos�b i zebranie ich w jeden typ z kt�rego mo�na je wybiera� (inne liczby sa dozwolone tylko s� nienazwane)
	UP = 5,
	DOWN = 7,
	RIGHT = 6,
	LEFT = 8,
	FOOD = 9
} matrix_state_t;


extern matrix_state_t matrix[MATRIX_ROW_COUNT][MATRIX_COL_COUNT];   

void matrix_init(void);
void matrix_set(uint8_t row, uint8_t col, matrix_state_t val);
void matrix_set_row(uint8_t row, matrix_state_t val);
void matrix_set_col(uint8_t col, matrix_state_t val);
void matrix_set_all(matrix_state_t val);

void matrix_update(void);