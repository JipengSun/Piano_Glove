// Breadboard example app
//
// Read from multiple analog sensors and control an RGB LED

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "nrf_delay.h"
#include "flex_sensors.h"


int main(void) {
  // Initialize I2C peripheral and driver
  printf("Board started!\n");
  // initialize ADC
  flex_sensors_init();
  // loop forever
  while (1) {
    nrf_delay_ms(1000);
  }
}

