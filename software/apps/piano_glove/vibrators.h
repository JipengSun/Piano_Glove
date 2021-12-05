#pragma once

#include "nrf_twi_mngr.h"

void motor_vibrate(int number);

// Chip address for motor controller
static const uint8_t DRV2605L_MOTOR_ADDRESS = 0x5A;

// motor controller
typedef enum {
    STATUS_REG = 0x00,
    MODE_REG = 0x01,
} DRV2605L_reg_t;

// Function prototypes

// Initialize and configure the DRV2605L accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void drv2605l_init(const nrf_twi_mngr_t* i2c);
