// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "adafruit_PCF8591.h"
#include "nrf_delay.h"

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Helper function to perform a 1-byte I2C read of a given register
//
// i2c_addr - address of the device to read from
// reg_addr - address of the register within the device to read
//
// returns 8-bit read value
static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr) {
  uint8_t rx_buf = 0;
  nrf_twi_mngr_transfer_t const read_transfer[] = {
    //TODO: implement me
    NRF_TWI_MNGR_WRITE(i2c_addr,&reg_addr,1,NRF_TWI_MNGR_NO_STOP),
    NRF_TWI_MNGR_READ(i2c_addr,&rx_buf,1,0)

  };
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

  return rx_buf;
}

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
  //TODO: implement me
  //Note: there should only be a single two-byte transfer to be performed
  //uint8_t rx_buf = 0;
  //int16_t write_data = (reg_addr << 8)|(data);
  u_int8_t write_arrary[] = {reg_addr, data};
  nrf_twi_mngr_transfer_t const write_transfer[] = {
    //TODO: implement me
    NRF_TWI_MNGR_WRITE(i2c_addr,write_arrary,2,0)
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);

  //return rx_buf;



}

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void lsm303agr_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;

  // ---Initialize Accelerometer---

  // Reboot acclerometer
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG5, 0x80);
  nrf_delay_ms(100); // needs delay to wait for reboot

  // Enable Block Data Update
  // Only updates sensor data when both halves of the data has been read
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG4, 0x80);

  // Configure accelerometer at 100Hz, normal mode (10-bit)
  // Enable x, y and z axes
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG1, 0x57);

  // Read WHO AM I register
  // Always returns the same value if working
  uint8_t result = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_WHO_AM_I_REG);
  //TODO: check the result of the Accelerometer WHO AM I register

  printf("Accelerometer: %x\n",result);

  // ---Initialize Magnetometer---

  // Reboot magnetometer
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_A, 0x40);
  nrf_delay_ms(100); // needs delay to wait for reboot

  // Enable Block Data Update
  // Only updates sensor data when both halves of the data has been read
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_C, 0x10);

  // Configure magnetometer at 100Hz, continuous mode
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_A, 0x0C);

  // Read WHO AM I register
  result = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_WHO_AM_I_REG);
  //TODO: check the result of the Magnetometer WHO AM I register
  printf("Magnetometer: %x\n",result);
  // ---Initialize Temperature---

  // Enable temperature sensor
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_TEMP_CFG_REG, 0xC0);
}

// Read the internal temperature sensor
//
// Return measurement as floating point value in degrees C
float lsm303agr_read_temperature(void) {
  //TODO: implement me
  uint8_t msb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_TEMP_H);
  uint8_t lsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_TEMP_L);
  int16_t temp = (msb << 8)|(lsb & 0xff);
  float ftemp = (float)temp * 1.0/256.0 + 25.0;
  return ftemp;
}

lsm303agr_measurement_t lsm303agr_read_accelerometer(void) {
  //TODO: implement me
  uint8_t xmsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_OUT_X_H);
  uint8_t xlsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_OUT_X_L);
  int16_t xacc = (xmsb << 8)|(xlsb & 0xff);
  int16_t xshift = (xacc >> 6);
  float fxacc = (float)xshift * 3.9/1000.0;

  uint8_t ymsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_OUT_Y_H);
  uint8_t ylsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_OUT_Y_L);
  int16_t yacc = (ymsb << 8)|(ylsb & 0xff);
  int16_t yshift = (yacc >> 6);
  float fyacc = (float)yshift * 3.9/1000.0;

  uint8_t zmsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_OUT_Z_H);
  uint8_t zlsb = i2c_reg_read(LSM303AGR_ACC_ADDRESS,LSM303AGR_ACC_OUT_Z_L);
  int16_t zacc = (zmsb << 8)|(zlsb & 0xff);
  int16_t zshift = (zacc >> 6);
  float fzacc = (float)zshift * 3.9/1000.0;
  lsm303agr_measurement_t measurement = {fxacc,fyacc,fzacc};
  return measurement;
}

lsm303agr_measurement_t lsm303agr_read_magnetometer(void) {
  //TODO: implement me
  uint8_t xmsb = i2c_reg_read(LSM303AGR_MAG_ADDRESS,LSM303AGR_MAG_OUT_X_H_REG);
  uint8_t xlsb = i2c_reg_read(LSM303AGR_MAG_ADDRESS,LSM303AGR_MAG_OUT_X_L_REG);
  int16_t xmag = (xmsb << 8)|(xlsb & 0xff);
  float fxmag = (float)xmag * 1.5 /10.0;

  uint8_t ymsb = i2c_reg_read(LSM303AGR_MAG_ADDRESS,LSM303AGR_MAG_OUT_Y_H_REG);
  uint8_t ylsb = i2c_reg_read(LSM303AGR_MAG_ADDRESS,LSM303AGR_MAG_OUT_Y_L_REG);
  int16_t ymag = (ymsb << 8)|(ylsb & 0xff);
  float fymag = (float)ymag * 1.5 /10.0;

  uint8_t zmsb = i2c_reg_read(LSM303AGR_MAG_ADDRESS,LSM303AGR_MAG_OUT_Z_H_REG);
  uint8_t zlsb = i2c_reg_read(LSM303AGR_MAG_ADDRESS,LSM303AGR_MAG_OUT_Z_L_REG);
  int16_t zmag = (zmsb << 8)|(zlsb & 0xff);
  float fzmag = (float)zmag * 1.5 /10.0;

  lsm303agr_measurement_t measurement = {fxmag,fymag,fzmag};
  return measurement;

}


float convert_angle() {
  lsm303agr_measurement_t acc = lsm303agr_read_accelerometer();

  float x = acc.x_axis;
  float y = acc.y_axis;
  float z = acc.z_axis;

  float x_sqr = pow(x,2);
  float y_sqr = pow(y,2);
  float sqr_rt = sqrt(x_sqr+y_sqr)/z;
  float phi = atan((double)sqr_rt);

  phi = phi*(180.0/M_PI);
  return phi;

}