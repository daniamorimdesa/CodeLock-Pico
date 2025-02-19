// oled_display.c

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "oled_display.h"

// Initializes the OLED display with I2C
void init_oled(ssd1306_t *oled) {
  i2c_init(i2c0, 400000);
  gpio_set_function(4, GPIO_FUNC_I2C); // SDA
  gpio_set_function(5, GPIO_FUNC_I2C); // SCL
  gpio_pull_up(4);
  gpio_pull_up(5);

  if (!ssd1306_init(oled, 128, 64, 0x3C, i2c0)) {
    printf("Error initializing OLED.\n");
  } else {
    oled_show_enter_password(oled);
  }
}

// Displays a formatted message on the OLED screen
void oled_printf(ssd1306_t *oled, const char *format, ...) {
  char buffer[64];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  ssd1306_clear(oled);
  ssd1306_draw_string(oled, 0, 0, 1, buffer);
  ssd1306_show(oled);
}

// Shows predefined messages on the OLED
void oled_show_enter_password(ssd1306_t *oled) {
  oled_printf(oled, "Enter the password:");
}

void oled_show_incorrect_password(ssd1306_t *oled) {
  oled_printf(oled, "Incorrect password!");
}

void oled_show_safe_open(ssd1306_t *oled) {
  oled_printf(oled, "<<< Safe Open >>>");
}

void oled_show_safe_closed(ssd1306_t *oled) {
  oled_printf(oled, "<<< Safe Closed >>>");
}

void oled_show_system_locked(ssd1306_t *oled) {
  oled_printf(oled, "System Locked!");
}

void oled_show_new_password_mode(ssd1306_t *oled) {
  oled_printf(oled, "Mode: New password");
}

void oled_show_password_reset(ssd1306_t *oled) {
  oled_printf(oled, "Password reset!");
}

void oled_show_password_saved(ssd1306_t *oled) {
  oled_printf(oled, "New password saved!");
}

void oled_show_password_input(ssd1306_t *oled, const char *password) {
  oled_printf(oled, "Password: %s", password);
}