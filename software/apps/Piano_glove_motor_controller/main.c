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
NRF_TWI_MNGR_DEF(twi_mngr_instance_1, 1, 1);
// NRF_TWI_MNGR_DEF(twi_mngr_instance_2, 1, 0);

int main(void)
{
    printf("Board started!\n");

    // Initialize I2C peripheral and driver
    nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
    // nrf_drv_twi_config_t i2c_config_1 = NRF_DRV_TWI_DEFAULT_CONFIG;
    nrf_drv_twi_config_t i2c_config_2 = NRF_DRV_TWI_DEFAULT_CONFIG;

    // middle
    i2c_config.scl = EDGE_P15;
    i2c_config.sda = EDGE_P16;
    i2c_config.frequency = NRF_TWIM_FREQ_100K;
    i2c_config.interrupt_priority = 0;
    nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

    // // right
    // i2c_config_1.scl = EDGE_P19;
    // i2c_config_1.sda = EDGE_P20;
    // i2c_config_1.frequency = NRF_TWIM_FREQ_100K;
    // i2c_config_1.interrupt_priority = 0;
    // nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config_2);

    // left
    i2c_config_2.scl = EDGE_P13;
    i2c_config_2.sda = EDGE_P14;
    i2c_config_2.frequency = NRF_TWIM_FREQ_100K;
    i2c_config_2.interrupt_priority = 0;
    nrf_twi_mngr_init(&twi_mngr_instance_1, &i2c_config_2);

    // Initialize the motor driver
    lsm303agr_init(&twi_mngr_instance, &twi_mngr_instance_1);
    // lsm303agr_init(&twi_mngr_instance);

    //TODO: implement me!

    // Loop forever
    while (1) {
        // Don't put any code in here. Instead put periodic code in a callback using a timer.
        nrf_delay_ms(1000);
    }
}
