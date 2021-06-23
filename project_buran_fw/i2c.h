/*
 * i2c.h
 *
 * Created: 12/06/2021 00:53:37
 * Author: Anton
 *
 * SERCOM0 I2C: PA14/PA15 Group C 
 * GCLK_SERCOMx_CORE, GCLK_SERCOM_SLOW 
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "main.h"
#include "LP5012PWR.h"

/**
 * Configures the I2C Peripheral 
 */
void i2c_configure(void);
/**
 * Reads the specified register and returns the result
 */
uint8_t i2c_read(uint8_t reg_addr);
/**
 * Writes to the specified register with the given data, returns
 * true if successful
 */
uint8_t i2c_write(uint8_t reg_addr, uint8_t data_to_write); 

#endif /* I2C_H_ */