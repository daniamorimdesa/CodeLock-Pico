// password_manager.h

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include "pico/stdlib.h"
#include "oled_display.h"

// Manages password validation
bool validate_password(const char *entered_password);
void save_new_password(const char *new_password, ssd1306_t *oled);
void handle_incorrect_attempt(ssd1306_t *oled);
bool is_locked(void);

// Handles keypad input and safe states
void handle_safe_open(char key, ssd1306_t *oled);
void handle_safe_closed(char key, ssd1306_t *oled);
void process_key_input(char key, ssd1306_t *oled);

#endif // PASSWORD_MANAGER_H