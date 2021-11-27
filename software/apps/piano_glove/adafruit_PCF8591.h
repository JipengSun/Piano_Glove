#include "nrf_twi_mngr.h"

#define PCF8591_DEFAULT_ADDR 0x48

void PCF8591_init(const nrf_twi_mngr_t* i2c);