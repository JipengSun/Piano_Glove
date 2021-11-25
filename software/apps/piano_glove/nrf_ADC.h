
#include "microbit_v2.h"
#include "nrfx_saadc.h"

void adc_init();

float adc_sample_blocking(uint8_t channel);

void print_flex_value(void);