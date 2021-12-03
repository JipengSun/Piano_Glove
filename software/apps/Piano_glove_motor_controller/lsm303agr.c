// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>

#include "lsm303agr.h"
#include "nrf_delay.h"

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;
static const nrf_twi_mngr_t* i2c_manager_1 = NULL;
// static const nrf_twi_mngr_t* i2c_manager_2 = NULL;

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
        //TODO: implement me
        NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
        NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 1, 0)
    };
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

    return rx_buf;
}

static uint8_t i2c_reg_read_1(uint8_t i2c_addr, uint8_t reg_addr)
{
    uint8_t rx_buf = 0;
    nrf_twi_mngr_transfer_t const read_transfer[] = {
        //TODO: implement me
        NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
        NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 1, 0)
    };
    nrf_twi_mngr_perform(i2c_manager_1, NULL, read_transfer, 2, NULL);

    return rx_buf;
}

// static uint8_t i2c_reg_read_2(uint8_t i2c_addr, uint8_t reg_addr)
// {
//     uint8_t rx_buf = 0;
//     nrf_twi_mngr_transfer_t const read_transfer[] = {
//         //TODO: implement me
//         NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
//         NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 1, 0)
//     };
//     nrf_twi_mngr_perform(i2c_manager_2, NULL, read_transfer, 2, NULL);

//     return rx_buf;
// }

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data)
{
    //TODO: implement me
    //Note: there should only be a single two-byte transfer to be performed
    u_int8_t write_arrary[] = { reg_addr, data };
    nrf_twi_mngr_transfer_t const write_transfer[] = {
        //TODO: implement me
        NRF_TWI_MNGR_WRITE(i2c_addr, write_arrary, 2, 0)
    };
    nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
}

static void i2c_reg_write_1(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data)
{
    //TODO: implement me
    //Note: there should only be a single two-byte transfer to be performed
    u_int8_t write_arrary[] = { reg_addr, data };
    nrf_twi_mngr_transfer_t const write_transfer[] = {
        //TODO: implement me
        NRF_TWI_MNGR_WRITE(i2c_addr, write_arrary, 2, 0)
    };
    nrf_twi_mngr_perform(i2c_manager_1, NULL, write_transfer, 1, NULL);
}

// static void i2c_reg_write_2(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data)
// {
//     //TODO: implement me
//     //Note: there should only be a single two-byte transfer to be performed
//     u_int8_t write_arrary[] = { reg_addr, data };
//     nrf_twi_mngr_transfer_t const write_transfer[] = {
//         //TODO: implement me
//         NRF_TWI_MNGR_WRITE(i2c_addr, write_arrary, 2, 0)
//     };
//     nrf_twi_mngr_perform(i2c_manager_2, NULL, write_transfer, 1, NULL);
// }

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void lsm303agr_init(const nrf_twi_mngr_t* i2c, const nrf_twi_mngr_t* i2c_1)
// void lsm303agr_init(const nrf_twi_mngr_t* i2c)
{
    i2c_manager = i2c;
    i2c_manager_1 = i2c_1;
    // i2c_manager_2 = i2c_2;

    // ---Initialize Motor Controller---
    nrf_delay_ms(100);

    // Reboot Motor Controller
    // LEFT
    // i2c_reg_write_1(DRV2605L_MOTOR_ADDRESS, MODE_REG, 0x03);
    // nrf_delay_ms(300); // needs delay to wait for reboot

    // i2c_reg_write_1(DRV2605L_MOTOR_ADDRESS, STATUS_REG, 0x88);
    // nrf_delay_ms(300);
    // uint8_t result_1 = i2c_reg_read_1(DRV2605L_MOTOR_ADDRESS, MODE_REG);
    // uint8_t result_2 = i2c_reg_read_1(DRV2605L_MOTOR_ADDRESS, STATUS_REG);
    // printf("LEFT: Check MODE_REG of the Motor Controller: %d\n", result_1);
    // printf("LEFT: Check STATUS_REG of the Motor Controller: %x\n", result_2);

    // // MIDLLE
    i2c_reg_write(DRV2605L_MOTOR_ADDRESS, MODE_REG, 0x02);
    nrf_delay_ms(300); // needs delay to wait for reboot

    // i2c_reg_write(DRV2605L_MOTOR_ADDRESS, STATUS_REG, 0x88);
    nrf_delay_ms(300);
    uint8_t result_3 = i2c_reg_read(DRV2605L_MOTOR_ADDRESS, MODE_REG);
    uint8_t result_4 = i2c_reg_read(DRV2605L_MOTOR_ADDRESS, STATUS_REG);
    printf("MIDDLE: Check MODE_REG of the Motor Controller: %d\n", result_3);
    printf("MIDDLE: Check STATUS_REG of the Motor Controller: %x\n", result_4);

    // // RIGHT
    // i2c_reg_write(DRV2605L_MOTOR_ADDRESS, MODE_REG, 0x02);
    // nrf_delay_ms(300); // needs delay to wait for reboot

    // i2c_reg_write(DRV2605L_MOTOR_ADDRESS, STATUS_REG, 0x88);
    // nrf_delay_ms(300);
    // uint8_t result_5 = i2c_reg_read(DRV2605L_MOTOR_ADDRESS, MODE_REG);
    // uint8_t result_6 = i2c_reg_read(DRV2605L_MOTOR_ADDRESS, STATUS_REG);
    // printf("RIGHT: Check MODE_REG of the Motor Controller: %d\n", result_5);
    // printf("RIGHT: Check STATUS_REG of the Motor Controller: %x\n", result_6);
}

// Read the internal temperature sensor
//
// Return measurement as floating point value in degrees C
float lsm303agr_read_temperature(void)
{
    //TODO: implement me

    return 0.0;
}

lsm303agr_measurement_t lsm303agr_read_accelerometer(void)
{
    //TODO: implement me

    lsm303agr_measurement_t measurement = { 0 };
    return measurement;
}

lsm303agr_measurement_t lsm303agr_read_magnetometer(void)
{
    //TODO: implement me

    lsm303agr_measurement_t measurement = { 0 };

    return measurement;
}
