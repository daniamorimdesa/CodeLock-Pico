/* Digital Safe with 4-Digit Password and OLED Display
  This project implements a digital safe controlled by a Raspberry Pi Pico.
  The system includes:
  - 4x4 matrix keypad for password input
  - OLED display for feedback
  - Servo motor to open/close the safe
  - Buzzer for audio alerts

  Usage instructions:
  - Default password: 1234
  - Enter a 4-digit password and press '#' to validate.
  - Press '*' to reset the input and enter the password again.
  - Press 'A' to set a new 4-digit password and confirm with '#'.
  - If the wrong password is entered 3 times, the system will lock for 10 seconds.
  - After the safe is opened, press 'C' to close it.

  Author: Daniela Amorim de Sá
  Electronic Engineer | Embedded Systems & IoT
  Project developed as part of the EmbarcaTech course.
  Access on GitHub:
  link
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "ssd1306.h"
#include "servo.h"
#include "buzzer.h"
#include "oled_display.h"
#include "led.h"
#include "keypad.h"
#include "password_manager.h"

// Global variables
static char entered_password[5];
static int password_pos = 0;
static bool changing_password = false;
static bool safe_open = false;
ssd1306_t oled;

// Main function
int main() {
  stdio_init_all();
  init_oled(&oled);
  led_init();
  servo_init();
  init_keypad();
  play_start_safe(BUZZER_PIN);

  while (true) {
    char key = read_keypad();
    if (key != '\0' && !is_locked()) {
      process_key_input(key, &oled);
      sleep_ms(200);
    }
  }
  return 0;
}