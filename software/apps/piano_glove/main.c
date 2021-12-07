// Breadboard example app

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "nrf_delay.h"
#include "flex_sensors.h"
#include "LED_matrix.h"
#include "vibrators.h"
#include "app_button.h"
//#include "song_selection.h"

#include "microbit_v2.h"
#include "nrf_twi_mngr.h"

int SCORE[];
// int SCORE[] = { 3, 8, 9 };
int score_length;

void song_selection(){

  // char song_name[] = "Jasmine";
  // int testSCORE[] = { 5, 6, 3, 3, 5, 6, 9, 1, 1, 8, 6, 5, 5, 6, 5 };

  // char song_name[] = "Happy Birthday";
  // int testSCORE[] = { 8,5,5,6,5,9,1,8,7,5,5,6,5,9,2,1};

   char song_name[] = "Shape of You";
   int testSCORE[] = { 1,2,3,2,1,1,2,2,6,2,1,1,2,6};


  display_string(song_name);
  memcpy(SCORE,testSCORE,sizeof(testSCORE));
  score_length = sizeof(testSCORE) /sizeof(testSCORE[0]);
  wait_confirm();
  char message[] = "OK";
  display_string(message);
}

int main(void) {
  // Initialize I2C peripheral and driver
  printf("Board started!\n");
  // initialize ADC
  flex_sensors_init();

  led_matrix_init();

  //button_init();

  song_selection();

  // loop forever
  while (1) {
    nrf_delay_ms(1000);
    printf("The length of the score is: %d\n",score_length);
    for(int i = 0; i < score_length; i++){
      LED_display(SCORE[i]);
      motor_vibrate(SCORE[i]);
      //nrf_delay_ms(500);
      wait_right_flex_signal(SCORE[i]);
    }
    char finish_message[] = "Good!";
    display_string(finish_message);
  }
}

