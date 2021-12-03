#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#include "app_timer.h"
#include "microbit_v2.h"

#include "nrfx_saadc.h"
#include "microbit_v2.h"
#include "nrf_ADC.h"
#include "adafruit_PCF8591.h"


unsigned long ain_pins[] = {NRF_SAADC_INPUT_AIN0, NRF_SAADC_INPUT_AIN1,NRF_SAADC_INPUT_AIN2,NRF_SAADC_INPUT_AIN3};

void saadc_event_callback(nrfx_saadc_evt_t const* _unused) {
  // don't care about saadc events
  // ignore this function
}

static void sample_timer_callback(void* _unused) {
  // Do things periodically here
  // TODO
  print_flex_value();
  print_PCF_volatage();
}

void adc_init() {
  // Initialize the SAADC
  nrfx_saadc_config_t saadc_config = {
    .resolution = NRF_SAADC_RESOLUTION_12BIT,
    .oversample = NRF_SAADC_OVERSAMPLE_DISABLED,
    .interrupt_priority = 4,
    .low_power_mode = false,
  };
  ret_code_t error_code = nrfx_saadc_init(&saadc_config, saadc_event_callback);
  APP_ERROR_CHECK(error_code);
  // Initialize temperature sensor channel
  for (int i = 0; i < 3; i++){
    nrf_saadc_channel_config_t temp_channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(ain_pins[i]);
    error_code = nrfx_saadc_channel_init(i, &temp_channel_config);
  }

  APP_ERROR_CHECK(error_code);

  // Global variables
  APP_TIMER_DEF(sample_timer);

  // initialize app timers
  app_timer_init();
  app_timer_create(&sample_timer, APP_TIMER_MODE_REPEATED, sample_timer_callback);
  // start timer
  // change the rate to whatever you want
  app_timer_start(sample_timer, 32768, NULL);


}

float adc_sample_blocking(uint8_t channel) {
  // read ADC counts (0-4095)
  // this function blocks until the sample is ready
  int16_t adc_counts = 0;
  ret_code_t error_code = nrfx_saadc_sample_convert(channel, &adc_counts);
  APP_ERROR_CHECK(error_code);

  // convert ADC counts to volts
  // 12-bit ADC with range from 0 to 3.6 Volts
  // TODO

  float voltage = (adc_counts/4095.0)*3.6;
  // return voltage measurement
  return voltage;
}


void print_flex_value(void){
  for(int i = 0; i < 3; i++){
    float fn1 = adc_sample_blocking(i);
    printf("Float Voltage of Channel %d: %f\n",i,fn1);
  }
  printf("\n");
}
