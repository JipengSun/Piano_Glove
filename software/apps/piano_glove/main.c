// Breadboard example app

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "nrf_delay.h"
#include "flex_sensors.h"
#include "LED_matrix.h"
#include "vibrators.h"

// int SCORE[] = {3,3,5,6,9,1,1,8,6,5,5,6,5};
int SCORE[] = { 3, 8, 9 };
int score_length = sizeof(SCORE) /sizeof(SCORE[0]);

int main(void) {
  // Initialize I2C peripheral and driver
  printf("Board started!\n");
  // initialize ADC
  flex_sensors_init();

  led_matrix_init();
  get_string("S", 0);
  nrf_delay_ms(1000);

  // loop forever
  while (1) {
    nrf_delay_ms(1000);
    printf("The length of the score is: %d\n",score_length);
    for(int i = 0; i < score_length; i++){
      LED_display(SCORE[i]);
      motor_vibrate(SCORE[i]);
      wait_right_flex_signal(SCORE[i]);
      nrf_delay_ms(3000);
    }
  }
}

