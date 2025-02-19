// led.c

#include "led.h"
#include "pico/stdlib.h"

// Initialize LEDs
void led_init() {
  gpio_init(GREEN_LED);
  gpio_set_dir(GREEN_LED, GPIO_OUT);
  gpio_put(GREEN_LED, 0);

  gpio_init(RED_LED);
  gpio_set_dir(RED_LED, GPIO_OUT);
  gpio_put(RED_LED, 0);
}