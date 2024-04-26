#pragma once
#include <stdint.h>		//biblioteka która dodaje typ zmiennie uint8_t (8bitowy unsingned int) to samo co unsigned char

#define MATRIX_ROW_COUNT 7   //Dodanie sta³ej wartoœci, kompilator zamienia wszystkie wyst¹pnie w kodzie na matrix-row... na 7
#define MATRIX_COL_COUNT 5

typedef enum {			//definiowanie typu zmiennej matrix_state_t zmienna mo¿e przyjmowaæ dwie wartoœæi Matrix off ON które sa równowa¿ne z 0 i 1 
	OFF = 0,		// polepsza to czytelnoœc kodu poniewa¿ wpisujmey zmiennie typu OFF która nie jest losow pojawiaj¹c¹ siê liczb¹ w kodzie 
	ON  = 1,		// jest to sposób na nazwanie liczb w jakiœ znacz¹cy sposób i zebranie ich w jeden typ z którego mo¿na je wybieraæ (inne liczby sa dozwolone tylko s¹ nienazwane)
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