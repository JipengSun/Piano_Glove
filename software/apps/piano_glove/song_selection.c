#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "microbit_v2.h"
#include "nrf_gpio.h"


#include <string.h>
#include "app_timer.h"

//#include "app_button.h"
#include <app_button.h>

/*
void song_selection(){
// Display current song name, waiting for confirm.
  char song_name[] = "Jasmine";
  display_string(song_name);
  SCORE[] = [ 5, 6, 3, 3, 5, 6, 9, 1, 1, 8, 6, 5, 5, 6, 5 ];
  wait_confirm();
  char message[] = "OK";
  display_string(message);
}
*/
int err_code;
int song_idx = 0;

static void button_handler(uint8_t pin_no, uint8_t button_action)
{
    if(button_action == APP_BUTTON_PUSH)
    {
        switch(pin_no)
        {
            case BTN_A:
            song_idx -= 1;
            song_idx %= 3;
            printf("Song index %d",song_idx);
                break;
            case BTN_B:
            song_idx += 1;
            song_idx %= 3;
            printf("Song index %d",song_idx);
                break;
            default:
                break;
        }
    }
}


void button_init(){
    app_button_cfg_t p_button[] = {  {BTN_A, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_PULLUP, button_handler},
                                            {BTN_B, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_PULLUP, button_handler}};
    err_code = app_button_init(p_button, sizeof(p_button) / sizeof(p_button[0]), 50);
    app_button_enable();
    printf("%d\n",err_code);
    
}

void test_button(){

}