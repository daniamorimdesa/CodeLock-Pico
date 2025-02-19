//buzzer.h

#ifndef BUZZER_H
#define BUZZER_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define BUZZER_PIN 1

// Configures PWM for the specified pin with frequency and duty cycle
void setup_pwm(uint pin, uint freq, float duty_cycle);

// Stops PWM on the specified pin
void stop_pwm(uint pin);

// Plays a tone on the specified pin for a duration in milliseconds
void play_tone(uint pin, uint freq, uint duration_ms, float duty_cycle);

void play_start_safe(uint pin);
void play_success_melody(uint pin);
void play_safe_closed_sound(uint pin);
void play_incorrect_password(uint pin);
void play_safe_locked(uint pin);
void play_safe_unlocked(uint pin);

#endif // BUZZER_H