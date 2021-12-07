#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "nrf_error.h"
#include "microbit_v2.h"
#include "nrf_delay.h"

#include "nrfx_saadc.h"
#include "nrf_twi_mngr.h"

#include "adafruit_PCF8591.h"
#include "nrf_ADC.h"
#include "vibrators.h"

#include "app_timer.h"

NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

extern float Chip_Flex_Value[];
extern u_int8_t PCF_Channel_1_Value;
extern u_int8_t PCF_Channel_2_Value;


volatile int trigger_states[5] = {0};
const float trigger_threshold[5] = {2.0,2.0,2.0,150,150};


static void sample_timer_callback(void* _unused) {
  // Do things periodically here
  update_flex_value();
  update_PCF_voltage();

  // Print the value out
  for(int i = 0; i <3; i++){
    printf("NRF Channel %d: %f\n",i,Chip_Flex_Value[i]);
  }
  printf("PCF Channel 1: %d\n",PCF_Channel_1_Value);
  printf("PCF Channel 2: %d\n",PCF_Channel_2_Value);
  printf("\n");
}

void flex_sensors_init(){
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = EDGE_P19;
  i2c_config.sda = EDGE_P20;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  i2c_config.interrupt_priority = 0;
  nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

  adc_init();
  PCF8591_init(&twi_mngr_instance);
  drv2605l_init(&twi_mngr_instance);


  // Global variables
  APP_TIMER_DEF(sample_timer);

  // initialize app timers
  app_timer_init();
  app_timer_create(&sample_timer, APP_TIMER_MODE_REPEATED, sample_timer_callback);
  // start timer
  // change the rate to whatever you want
  app_timer_start(sample_timer, 62768, NULL);

};

void update_trigger_states(){
  float flex_values[5] = {Chip_Flex_Value[0],Chip_Flex_Value[1],Chip_Flex_Value[2],(float)PCF_Channel_1_Value,(float)PCF_Channel_2_Value};
  for(int i = 0; i < 5; i++){
    if(flex_values[i] <= trigger_threshold[i]){
      trigger_states[i] = 1;
      printf("Channel % d triggered with value %f\n",i,flex_values[i]);
    }
    else{
      trigger_states[i] = 0;
    }
  }


}

void wait_right_flex_signal(int number){
  if(number > 7){
    printf("Move left or right.\n");
    nrf_delay_ms(2000);
  }
  else if (number > 5){
    number = 5;
  } else{
    update_trigger_states();
    while(trigger_states[number-1]!=1){
      nrf_delay_ms(200);
      update_trigger_states();
    }
    printf("Finger %d Triggered!\n", number);
  }
};

void wait_confirm(){
  bool confirm = false;
  while(!confirm){
    update_trigger_states();
    int sum = 0;
    for(int i = 0; i < 5; i++){
      sum += trigger_states[i];
    }
    if (sum > 1){
      confirm = true;
    }
    nrf_delay_ms(200);
  }
}


