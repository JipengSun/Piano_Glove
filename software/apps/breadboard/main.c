// Breadboard example app
//
// Read from multiple analog sensors and control an RGB LED

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_saadc.h"

#include "microbit_v2.h"

// Digital outputs
// Breakout pins 13, 14, and 15
// These are GPIO pin numbers that can be used in nrf_gpio_* calls
#define LED_BLUE   EDGE_P13
#define LED_GREEN EDGE_P14
#define LED_RED  EDGE_P15

// Digital inputs
// Breakout pin 16
// These are GPIO pin numbers that can be used in nrf_gpio_* calls
#define SWITCH_IN EDGE_P16

// Analog inputs
// Breakout pins 1 and 2
// These are GPIO pin numbers that can be used in ADC configurations
// AIN1 is breakout pin 1. AIN2 is breakout pin 2.
#define ANALOG_TEMP_IN  NRF_SAADC_INPUT_AIN1
#define ANALOG_LIGHT_IN NRF_SAADC_INPUT_AIN2

// ADC channel configurations
// These are ADC channel numbers that can be used in ADC calls
#define ADC_TEMP_CHANNEL  0
#define ADC_LIGHT_CHANNEL 1

// Global variables
APP_TIMER_DEF(sample_timer);

// Function prototypes
static void gpio_init(void);
static void adc_init(void);
static float adc_sample_blocking(uint8_t channel);

static void sample_timer_callback(void* _unused) {
  // Do things periodically here
  // TODO
}

static void saadc_event_callback(nrfx_saadc_evt_t const* _unused) {
  // don't care about saadc events
  // ignore this function
}

static void gpio_init(void) {
  // Initialize output pins
  // TODO
  nrf_gpio_pin_dir_set(EDGE_P13,NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(EDGE_P14,NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(EDGE_P15,NRF_GPIO_PIN_DIR_OUTPUT);

  // Set LEDs off initially
  // TODO
  nrf_gpio_pin_set(EDGE_P13);
  nrf_gpio_pin_set(EDGE_P14);
  nrf_gpio_pin_set(EDGE_P15);


  //nrf_gpio_pin_clear(EDGE_P13);
  //nrf_gpio_pin_clear(LED_BLUE);
  //nrf_gpio_pin_clear(EDGE_P15);

  //rf_gpio_pin_clear(LED_BLUE);

  // Initialize input pin
  // TODO
  nrf_gpio_pin_dir_set(EDGE_P16,NRF_GPIO_PIN_DIR_INPUT);
  //printf(1);
  
}



static void adc_init(void) {
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
  nrf_saadc_channel_config_t temp_channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(ANALOG_TEMP_IN);
  error_code = nrfx_saadc_channel_init(ADC_TEMP_CHANNEL, &temp_channel_config);
  APP_ERROR_CHECK(error_code);

  // Initialize light sensor channel
  nrf_saadc_channel_config_t light_channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(ANALOG_LIGHT_IN);
  error_code = nrfx_saadc_channel_init(ADC_LIGHT_CHANNEL, &light_channel_config);
  APP_ERROR_CHECK(error_code);
}

static float adc_sample_blocking(uint8_t channel) {
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


static int light_state_helper(float voltage){
  if(voltage > 2.79){
    printf("Light State: Very Bright.\n");
    return 2;
  } else if(voltage < 1.9){
    printf("Light State: Dark.\n");
    return 0;
  } else{
    printf("Light State: Medium Bright.\n");
    return 1;
  }
}

static float temp_state_helper(float voltage){
  float temp_resis = ((3.3-voltage)/voltage)*10000.0;
  // Test the lab quiz.
  //temp_resis = 2978.0;
  float r_infinity = 10000.0 * exp(-3950.0/298.15);
  float temp = 3950.0/(log(temp_resis/r_infinity));
  float temp_c = temp - 273;
  printf("Celsius Temprature is %f",temp_c);
  return temp_c;

}

static void led_control(int light_status, float temp_status){
  if(light_status == 0){
    nrf_gpio_pin_clear(LED_RED);
  } else{
    nrf_gpio_pin_set(LED_RED);
  }

  if(temp_status<26.0){
    nrf_gpio_pin_set(LED_GREEN);
  }
  else{
    nrf_gpio_pin_clear(LED_GREEN);
  }

  if(nrf_gpio_pin_read(EDGE_P16) == 1){
    nrf_gpio_pin_clear(LED_BLUE);
  } else{
    nrf_gpio_pin_set(LED_BLUE);
  }


}


int main(void) {
  printf("Board started!\n");
  
  // initialize GPIO
  gpio_init();

  // initialize ADC
  adc_init();

  // initialize app timers
  app_timer_init();
  app_timer_create(&sample_timer, APP_TIMER_MODE_REPEATED, sample_timer_callback);

  // start timer
  // change the rate to whatever you want
  app_timer_start(sample_timer, 32768, NULL);

  // loop forever
  while (1) {
    // Don't put any code in here. Instead put periodic code in `sample_timer_callback()`
    printf("Switch Status: %d \n",nrf_gpio_pin_read(EDGE_P16));
    float fn = adc_sample_blocking(ADC_LIGHT_CHANNEL);
    float fn1 = adc_sample_blocking(ADC_TEMP_CHANNEL);
    printf("Float Voltage of Channel 2: %f\n",fn);
    printf("Float Voltage of Channel 1: %f\n",fn1);
    int light_status = light_state_helper(fn);
    float temp_status = temp_state_helper(fn1);
    //temp_state_helper(fn1);
    led_control(light_status,temp_status);

    nrf_delay_ms(1000);
  }
}

