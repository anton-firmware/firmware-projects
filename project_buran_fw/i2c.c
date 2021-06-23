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
	
	SERCOM0->I2CM.BAUD.bit.BAUD = 0x13;
	
	SERCOM0->I2CM.CTRLA.bit.ENABLE = 1; // Enable I2C
	
	SERCOM0->I2CM.STATUS.bit.BUSSTATE = 0x1; // Force I2C into idle state
	while(SERCOM0->I2CM.SYNCBUSY.bit.SYSOP);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

uint8_t i2c_read(uint8_t reg_addr)
{	
	SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_WRITE;
	
	if(SERCOM0->I2CM.STATUS.bit.BUSSTATE == 0x2 && !SERCOM0->I2CM.STATUS.bit.RXNACK) // The MCU has the bus and we have received an ACK, we can now send data
	{
		uint8_t received = 0;
		SERCOM0->I2CM.DATA.reg = reg_addr;
		SERCOM0->I2CM.CTRLB.bit.CMD = 0x1; // repeated start
		
		SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_READ;
		
		received = SERCOM0->I2CM.DATA.reg;	
		SERCOM0->I2CM.CTRLB.bit.CMD = 0x3; // STOP condition
		
		return received;
	}
}

uint8_t i2c_write(uint8_t reg_addr, uint8_t data_to_write)
{
	SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_WRITE;
	
	if(SERCOM0->I2CM.STATUS.bit.BUSSTATE == 0x2 && !SERCOM0->I2CM.STATUS.bit.RXNACK) // The MCU has the bus and we have received an ACK, we can now send data
	{
		SERCOM0->I2CM.DATA.reg = reg_addr;
		while(SERCOM0->I2CM.STATUS.bit.RXNACK);
		SERCOM0->I2CM.DATA.reg = data_to_write;
		SERCOM0->I2CM.CTRLB.bit.CMD = 0x3; // STOP condition
	}	 
	
	return (i2c_read(reg_addr) == data_to_write);
}