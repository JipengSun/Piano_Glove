#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"
#include "vibrators.h"

#include "microbit_v2.h"
#include <math.h>
#include <stdio.h>

void motor_vibrate(int number){
    nrf_gpio_cfg_output(EDGE_P15);
    nrf_gpio_pin_clear(EDGE_P15);
    nrf_gpio_cfg_output(EDGE_P14);
    nrf_gpio_pin_clear(EDGE_P14);
    if (number == 8){
        nrf_gpio_pin_set(EDGE_P15);
    } else if (number == 9) {
        nrf_gpio_pin_set(EDGE_P14);
    }
}

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Helper function to perform a 1-byte I2C read of a given register
//
// i2c_addr - address of the device to read from
// reg_addr - address of the register within the device to read
//
// returns 8-bit read value
static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr)
{
    uint8_t rx_buf = 0;
    nrf_twi_mngr_transfer_t const read_transfer[] = {
        // TODO: implement me
        NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
        NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 1, 0)
    };
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

    return rx_buf;
}

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data)
{
    // TODO: implement me
    // Note: there should only be a single two-byte transfer to be performed
    u_int8_t write_arrary[] = { reg_addr, data };
    nrf_twi_mngr_transfer_t const write_transfer[] = {
        // TODO: implement me
        NRF_TWI_MNGR_WRITE(i2c_addr, write_arrary, 2, 0)
    };
    nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
}

// Initialize and configure the DRV2605L accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void drv2605l_init(const nrf_twi_mngr_t* i2c)
// void drv2605l_init(const nrf_twi_mngr_t* i2c)
{
    i2c_manager = i2c;

    // ---Initialize Motor Controller---
    nrf_delay_ms(100);

    // Reboot Motor Controller
    // MIDLLE
    i2c_reg_write(DRV2605L_MOTOR_ADDRESS, MODE_REG, 0x01);
    nrf_delay_ms(300); // needs delay to wait for reboot

    // i2c_reg_write(DRV2605L_MOTOR_ADDRESS, STATUS_REG, 0x88);
    nrf_delay_ms(300);
    uint8_t result_3 = i2c_reg_read(DRV2605L_MOTOR_ADDRESS, MODE_REG);
    uint8_t result_4 = i2c_reg_read(DRV2605L_MOTOR_ADDRESS, STATUS_REG);
    printf("MIDDLE: Check MODE_REG of the Motor Controller: %d\n", result_3);
    printf("MIDDLE: Check STATUS_REG of the Motor Controller: %x\n", result_4);
}