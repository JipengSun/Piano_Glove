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

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

void PCF8591_init(const nrf_twi_mngr_t* i2c){
  i2c_manager = i2c;
};

void PCF8591_write(int channel){
  uint8_t wr_buf;
  if(channel == 0){
    wr_buf = 0x00;
  }
  else if (channel == 1){
    wr_buf = 0x01;
  }
  nrf_twi_mngr_transfer_t const read_transfer[] = {
    //TODO: implement me
  NRF_TWI_MNGR_WRITE(PCF8591_DEFAULT_ADDR,&wr_buf,1,0),
  };
  int s = nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 1, NULL);

}

uint8_t PCF8591_read(){
  uint8_t rx_buf[4] = {0};
  nrf_twi_mngr_transfer_t const read_transfer1[] = {
    //TODO: implement me
    NRF_TWI_MNGR_READ(PCF8591_DEFAULT_ADDR,rx_buf,2,0)
  };
  int s1 = nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer1, 1, NULL);
  //printf("0x%x 0x%x 0x%x 0x%x\n",rx_buf[0],rx_buf[1],rx_buf[2],rx_buf[3]);
  return rx_buf[1];
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
    printf("\n");
}

void print_PCF_volatage(){
  uint8_t result;
  PCF8591_write(0);
  result = PCF8591_read();
  printf("The value of PCF ADC channel 1 is: %d\n",result);
  //printBits(sizeof(result),&result);

  PCF8591_write(1);
  result = PCF8591_read();
  printf("The value of PCF ADC channel 2 is: %d\n",result);
  //printBits(sizeof(result),&result);
};