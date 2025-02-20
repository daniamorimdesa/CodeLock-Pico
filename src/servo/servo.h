// servo.h

#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 10 

void servo_init(void);
void servo_move(uint angle);
void servo_open();
void servo_closed();

#endif // SERVO_H