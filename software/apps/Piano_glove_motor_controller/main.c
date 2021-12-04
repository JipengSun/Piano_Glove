// I2C sensors app
//
// Read from I2C accelerometer/magnetometer on the Microbit

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_delay.h"
#include "nrf_twi_mngr.h"

#include "lsm303agr.h"
#include "microbit_v2.h"

// Global variables
NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

int main(void)
{
    printf("Board started!\n");

    // Initialize I2C peripheral and driver
    nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;

    // middle
    i2c_config.scl = EDGE_P19;
    i2c_config.sda = EDGE_P20;
    i2c_config.frequency = NRF_TWIM_FREQ_100K;
    i2c_config.interrupt_priority = 0;
    nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

    // Initialize the motor driver
    lsm303agr_init(&twi_mngr_instance);

    // trigger the right one
    nrf_gpio_cfg_output(EDGE_P15);
    nrf_gpio_pin_clear(EDGE_P15);

    // trigger the left one
    nrf_gpio_cfg_output(EDGE_P14);
    nrf_gpio_pin_clear(EDGE_P14);

    // Loop forever
    while (1) {
        // Don't put any code in here. Instead put periodic code in a callback using a timer.
        nrf_gpio_pin_set(EDGE_P15);
        nrf_delay_ms(3000);
        nrf_gpio_pin_set(EDGE_P14);
        nrf_gpio_pin_clear(EDGE_P15);
        nrf_delay_ms(3000);
        nrf_gpio_pin_clear(EDGE_P14);
    }
}
