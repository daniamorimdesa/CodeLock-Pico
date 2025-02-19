// oled_display.h

#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include "ssd1306.h"

// Function prototypes
void init_oled(ssd1306_t *oled);
void oled_printf(ssd1306_t *oled, const char *format, ...);
void oled_show_enter_password(ssd1306_t *oled);
void oled_show_incorrect_password(ssd1306_t *oled);
void oled_show_safe_open(ssd1306_t *oled);
void oled_show_safe_closed(ssd1306_t *oled);
void oled_show_system_locked(ssd1306_t *oled);
void oled_show_new_password_mode(ssd1306_t *oled);
void oled_show_password_reset(ssd1306_t *oled);
void oled_show_password_saved(ssd1306_t *oled);
void oled_show_password_input(ssd1306_t *oled, const char *password);

#endif // OLED_DISPLAY_H