// servo.c

#include "servo.h"

//Initializes the PWM for the servo motor.
//The PWM frequency is set to 50 Hz (common for servos) with a 20 ms period
void servo_init(void) {
  gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);  // Set the servo pin as PWM
  uint slice1 = pwm_gpio_to_slice_num(SERVO_PIN);
  
  pwm_set_clkdiv(slice1, 64.0f);  // Set clock divider for 50 Hz
  pwm_set_wrap(slice1, 20000);    // Set PWM period to 20 ms (20000 counts)
  pwm_set_gpio_level(SERVO_PIN, 0);  // Initial pulse width set to 0
  pwm_set_enabled(slice1, true);  // Enable the PWM output
}

//Moves the servo to the specified angle (0 to 180 degrees)
void servo_move(uint angle) {
  if (angle > 180) angle = 180;  // Limit angle to 180 degrees
  uint pulse_width = 870 + (angle * 2000 / 180);  // Map angle to pulse width (870 to 2870)
  pwm_set_gpio_level(SERVO_PIN, pulse_width);
}

//Opens the safe by moving the servo to 0 degrees, then to 90 degrees
void servo_open() { // simulates the door opening process
  servo_move(0);
  sleep_ms(1000);
  servo_move(90);
  sleep_ms(1000);
}

// Closes the safe by moving the servo to 180 degrees, then back to 0 degrees
void servo_closed() { // simulates the door closing process
  servo_move(180);
  sleep_ms(1000);
  servo_move(0);
}
