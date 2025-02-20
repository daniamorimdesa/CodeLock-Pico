// keypad.c

#include "keypad.h"

// Pin definitions for the 4x4 matrix keypad
const uint8_t row_pins[ROWS] = {28, 27, 26, 22};
const uint8_t col_pins[COLS] = {21, 20, 19, 18};
const char keypad[ROWS][COLS] = {
    {'1', '2', '3', 'A'},  // 'A' is used to set a new password
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},  // 'C' is used to close the safe
    {'*', '0', '#', 'D'}   // '*' resets input, '#' validates
};

// Initializes the keypad rows as outputs and columns as inputs
void init_keypad(void) {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 0);
    }
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_down(col_pins[i]);
    }
}

// Reads input from the keypad and returns the pressed key
char read_keypad(void) {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(row_pins[row], 1); // Set the current row high
        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col])) { // Check if the key is pressed
                gpio_put(row_pins[row], 0); // Reset the row to low
                return keypad[row][col]; // Return the pressed key
            }
        }
        gpio_put(row_pins[row], 0); // Reset the row to low
    }
    return '\0'; // Return null if no key is pressed
}