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

/**
 * \brief 
 * Configures the I2C Peripheral 
 * \param 
 * 
 * \return void
 */
void i2c_configure(void);
void i2c_read();

#endif /* I2C_H_ */