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
// NRF_TWI_MNGR_DEF(twi_mngr_instance_1, 1, 1);
NRF_TWI_MNGR_DEF(twi_mngr_instance_2, 1, 1);

int main(void)
{
    printf("Board started!\n");

    // Initialize I2C peripheral and driver
    nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
    // nrf_drv_twi_config_t i2c_config_1 = NRF_DRV_TWI_DEFAULT_CONFIG;
    nrf_drv_twi_config_t i2c_config_2 = NRF_DRV_TWI_DEFAULT_CONFIG;

    // middle
    i2c_config.scl = EDGE_P19;
    i2c_config.sda = EDGE_P20;
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
    nrf_twi_mngr_init(&twi_mngr_instance_2, &i2c_config_2);

    // Initialize the motor driver
    lsm303agr_init(&twi_mngr_instance, &twi_mngr_instance_2);
    // lsm303agr_init(&twi_mngr_instance);

    // middle
    // nrf_gpio_cfg_output(EDGE_P15);
    // nrf_gpio_pin_set(EDGE_P15);
    // uint32_t check = nrf_gpio_pin_read(EDGE_P15);
    // printf("After set, status: %ld\n", check);
    // nrf_delay_ms(300);
    // nrf_gpio_pin_clear(EDGE_P15);
    // check = nrf_gpio_pin_read(EDGE_P15);
    // printf("After clear, status: %ld\n", check);
    // nrf_delay_ms(30000);
    // nrf_gpio_pin_set(EDGE_P15);

    // Loop forever
    while (1) {
        // Don't put any code in here. Instead put periodic code in a callback using a timer.
        nrf_gpio_pin_set(EDGE_P15);
        nrf_delay_ms(3000);
        nrf_gpio_pin_clear(EDGE_P15);
        nrf_delay_ms(3000);
    }
}
