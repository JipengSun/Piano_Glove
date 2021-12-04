#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "nrf_error.h"
#include "microbit_v2.h"

#include "nrfx_saadc.h"
#include "nrf_twi_mngr.h"

#include "adafruit_PCF8591.h"
#include "nrf_ADC.h"

#include "app_timer.h"

NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

static void sample_timer_callback(void* _unused) {
  // Do things periodically here
  print_flex_value();
  print_PCF_volatage();
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

  // Global variables
  APP_TIMER_DEF(sample_timer);

  // initialize app timers
  app_timer_init();
  app_timer_create(&sample_timer, APP_TIMER_MODE_REPEATED, sample_timer_callback);
  // start timer
  // change the rate to whatever you want
  app_timer_start(sample_timer, 62768, NULL);

};

void wait_right_flex_signal(int number){
    

};


