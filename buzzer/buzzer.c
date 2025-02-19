//buzzer.c

#include "buzzer.h"

void setup_pwm(uint pin, uint freq, float duty_cycle) {
  gpio_set_function(pin, GPIO_FUNC_PWM); // Sets the pin for PWM

  uint slice_num = pwm_gpio_to_slice_num(pin);
  uint channel = pwm_gpio_to_channel(pin);

  uint32_t clock = 125000000; // Pico clock frequency (125 MHz)
  uint32_t divider16 = clock / freq / 4096 + (clock % (freq * 4096) != 0);
  pwm_set_clkdiv(slice_num, divider16 / 16.0f);

  // Sets the duty cycle
  uint32_t level = (uint32_t)(4095 * duty_cycle);
  pwm_set_wrap(slice_num, 4095);
  pwm_set_chan_level(slice_num, channel, level);

  pwm_set_enabled(slice_num, true); // Enables PWM
}

void stop_pwm(uint pin) {
  uint slice_num = pwm_gpio_to_slice_num(pin);
  uint channel = pwm_gpio_to_channel(pin);

  pwm_set_chan_level(slice_num, channel, 0); // Disables PWM
  pwm_set_enabled(slice_num, false);         // Disables the slice
}

void play_tone(uint pin, uint freq, uint duration_ms, float duty_cycle) {
  setup_pwm(pin, freq, duty_cycle);
  sleep_ms(duration_ms);
  stop_pwm(pin);
}

// Safe startup sound
void play_start_safe(uint pin) {
  play_tone(pin, 100, 50, 0.5);
}

// Function to play the success melody (safe open)
void play_success_melody(uint pin) {
  play_tone(pin, 262, 200, 0.5); // Buzzer pin, note frequency, duration in ms, duty cycle
  sleep_ms(75); // Pause between notes
  play_tone(pin, 294, 200, 0.5);
  sleep_ms(75);
  play_tone(pin, 330, 200, 0.5);
  sleep_ms(75);
  play_tone(pin, 349, 200, 0.5);
  sleep_ms(75);
  play_tone(pin, 392, 400, 0.5);
  sleep_ms(75);
}

// Function to indicate safe closing with a sound pattern
void play_safe_closed_sound(uint pin) {
  play_tone(pin, 800, 200, 0.5); // Short beep
  sleep_ms(100);
  play_tone(pin, 800, 200, 0.5); // Short beep
  sleep_ms(100);
  play_tone(pin, 600, 400, 0.5); // Long beep
  sleep_ms(100);
}

// Invalid password sound
void play_incorrect_password(uint pin) {
  play_tone(pin, 500, 500, 0.5);
}

// Safe locked sound
void play_safe_locked(uint pin) {
  play_tone(pin, 100, 500, 0.5); // Lock sound
}

// Safe unlocked sound
void play_safe_unlocked(uint pin) {
  play_tone(pin, 600, 300, 0.5); // Unlock sound
}