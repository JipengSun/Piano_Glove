// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "nrf_error.h"

#include "adafruit_PCF8591.h"
#include "nrf_delay.h"

/*


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
*/

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

void PCF8591_init(const nrf_twi_mngr_t* i2c){

  i2c_manager = i2c;
  uint8_t wr_buf = 0x00;

  uint8_t rx_buf = 0;
  nrf_twi_mngr_transfer_t const read_transfer[] = {
    //TODO: implement me
  NRF_TWI_MNGR_WRITE(PCF8591_DEFAULT_ADDR,&wr_buf,1,NRF_TWI_MNGR_NO_STOP),
  NRF_TWI_MNGR_READ(PCF8591_DEFAULT_ADDR,&rx_buf,1,0)

  };
  int s = nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);


  int j = rx_buf;
  printf("LOOK!%d",j);
}
