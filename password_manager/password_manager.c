// password_manager.c

#include <string.h>
#include "password_manager.h"
#include "buzzer.h"
#include "servo.h"
#include "led.h"
#include "keypad.h"

// Password and lock control
static char correct_password[5] = "1234";
static int wrong_attempts = 0;
static bool locked = false;
static bool safe_open = false;
static char entered_password[5];
static int password_pos = 0;
static bool changing_password = false;
static bool verifying_old_password = false; // flag to verify current password
static char temp_new_password[5];  // Temporarily stores new password before confirmation

// Validates the entered password
bool validate_password(const char *entered_password) {
  return strcmp(entered_password, correct_password) == 0;
}

// Saves a new password
void save_new_password(const char *new_password, ssd1306_t *oled) {
  strcpy(correct_password, new_password);
  oled_show_password_saved(oled);
  sleep_ms(2000);
  oled_show_enter_password(oled);
}

// Handles incorrect password attempts
void handle_incorrect_attempt(ssd1306_t *oled) {
  wrong_attempts++;
  oled_show_incorrect_password(oled);

  for (int i = 0; i < 3; i++) { // Blink red LED 3 times
    play_incorrect_password(BUZZER_PIN);
    gpio_put(RED_LED, 1);
    sleep_ms(200);
    gpio_put(RED_LED, 0);
    sleep_ms(200);
  }

  sleep_ms(2000);
  oled_show_enter_password(oled);

  if (wrong_attempts >= 3) { // Lock system after 3 failed attempts
    locked = true;
    gpio_put(RED_LED, 1);
    oled_show_system_locked(oled);
    play_safe_locked(BUZZER_PIN);
    sleep_ms(10000); // Lock duration
    locked = false;
    gpio_put(RED_LED, 0);
    play_safe_unlocked(BUZZER_PIN);
    oled_show_enter_password(oled);
    wrong_attempts = 0;
  }
}

// Returns the lock status
bool is_locked(void) {
  return locked;
}

// Handles input when the safe is open
void handle_safe_open(char key, ssd1306_t *oled) {
  if (key == 'C') {  // Close the safe
    servo_closed();
    oled_show_safe_closed(oled);
    play_safe_closed_sound(BUZZER_PIN);
    gpio_put(GREEN_LED, 0);  // Turn off the green LED when the safe closes
    sleep_ms(2000);
    oled_show_enter_password(oled);
    safe_open = false;
  }
}

// Handles input when the safe is closed
void handle_safe_closed(char key, ssd1306_t *oled) {
  if (key == '#') {  // Confirm password entry
    if (changing_password) {
      if (verifying_old_password) {
        if (validate_password(entered_password)) {
          verifying_old_password = false;
          oled_show_new_password_mode(oled);
          memset(entered_password, 0, sizeof(entered_password));
          password_pos = 0;
        } else {
          oled_show_incorrect_password(oled);
          sleep_ms(2000);
          oled_show_enter_password(oled);
          changing_password = false;
          verifying_old_password = false;
          password_pos = 0;
          memset(entered_password, 0, sizeof(entered_password));
        }
      } else {  // Now we save the new password after confirming the old one
        save_new_password(entered_password, oled);
        oled_show_password_saved(oled);
        sleep_ms(2000);
        oled_show_enter_password(oled);
        changing_password = false;
        password_pos = 0;
        memset(entered_password, 0, sizeof(entered_password));
      }
    } else {  // Normal password validation
      if (validate_password(entered_password)) {
        gpio_put(GREEN_LED, 1);  // Turn on the green LED when the safe opens
        oled_show_safe_open(oled);
        play_success_melody(BUZZER_PIN);
        servo_open();
        safe_open = true;
      } else {
        handle_incorrect_attempt(oled);
      }
      password_pos = 0;
      memset(entered_password, 0, sizeof(entered_password));
    }

  } else if (key == '*') {  // Reset password input
    password_pos = 0;
    memset(entered_password, 0, sizeof(entered_password));
    oled_show_password_reset(oled);

  } else if (key == 'A') {  // Start password change process
    changing_password = true;
    verifying_old_password = true;
    oled_show_enter_old_password(oled);
    password_pos = 0;
    memset(entered_password, 0, sizeof(entered_password));

  } else if (password_pos < sizeof(entered_password) - 1) {  // Input password
    entered_password[password_pos++] = key;
    entered_password[password_pos] = '\0';
    oled_show_password_input(oled, entered_password);
  }
}

// Processes key input and delegates to the correct handler
void process_key_input(char key, ssd1306_t *oled) {
  if (safe_open) {
    handle_safe_open(key, oled);
  } else {
    handle_safe_closed(key, oled);
  }
}
