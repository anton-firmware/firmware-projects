/*
 * i2c.c
 *
 * Created: 12/06/2021 17:01:09
 *  Author: Anon
 */ 

#include "i2c.h"

// GCLK_SERCOMx_CORE
// SERCOM0 I2C: PA14/PA15 Group C 

void i2c_configure()
{
	/// SETUP THE CLOCKS ///////////////////////////////////////////////////////////////////////////////////////
	PM->APBCMASK.bit.SERCOM0_ = 1; // Enable CLK_SERCOM0_APB (Enabled by default lol?)
	GCLK->CLKCTRL.reg = (GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM0_CORE | (1 << GCLK_CLKCTRL_CLKEN_Pos));
	GCLK->CLKCTRL.reg = (GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_ID_SERCOMX_SLOW | (1 << GCLK_CLKCTRL_CLKEN_Pos));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/// SETUP THE PORT /////////////////////////////////////////////////////////////////////////////////////////
	PORT->Group[0].PINCFG[PIN_PA14].bit.PMUXEN = 1; // Pin Multiplex enable
	PORT->Group[0].PINCFG[PIN_PA15].bit.PMUXEN = 1; // Pin Multiplex enable
	
	PORT->Group[0].PMUX[7].bit.PMUXE = PINMUX_PA14C_SERCOM0_PAD0;
	PORT->Group[0].PMUX[7].bit.PMUXO = PINMUX_PA15C_SERCOM0_PAD1;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/// SETUP THE I2C //////////////////////////////////////////////////////////////////////////////////////////
	
	SERCOM0->I2CM.CTRLA.reg |=  SERCOM_I2CM_CTRLA_MODE_I2C_MASTER_Val << SERCOM_I2CM_CTRLA_MODE_Pos; // I2C in master mode
	while(SERCOM0->I2CM.SYNCBUSY.bit.SYSOP);
	SERCOM0->I2CM.CTRLA.bit.SDAHOLD = 0x2;
	while(SERCOM0->I2CM.SYNCBUSY.bit.SYSOP);
	SERCOM0->I2CM.CTRLB.bit.SMEN = 1; // Enable Smart Mode
	while(SERCOM0->I2CM.SYNCBUSY.bit.SYSOP);
	
	SERCOM0->I2CM.BAUD.bit.BAUD = 0xFF;
	
	SERCOM0->I2CM.STATUS.bit.BUSSTATE = 0x1; // Force I2C into idle state
	
	while(SERCOM0->I2CM.SYNCBUSY.bit.SYSOP);
	
	SERCOM0->I2CM.CTRLA.bit.ENABLE = 1; // Enable I2C
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void i2c_read()
{
	SERCOM0->I2CM.DATA.reg = 0x01; // SLAVE 0, READ DIRECTION
}