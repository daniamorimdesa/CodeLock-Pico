// keypad.h

#ifndef KEYPAD_H
#define KEYPAD_H

#include "pico/stdlib.h"

// Number of rows and columns in the keypad
#define ROWS 4
#define COLS 4

// Keypad pin definitions
extern const uint8_t row_pins[ROWS];
extern const uint8_t col_pins[COLS];
extern const char keypad[ROWS][COLS];

// Initializes the keypad GPIOs
void init_keypad();

/* Reads a key from the keypad, returns the character pressed or 
'\0' if no key is pressed*/
char read_keypad();

#endif // KEYPAD_H