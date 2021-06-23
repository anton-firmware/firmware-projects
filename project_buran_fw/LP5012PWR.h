/*
 * LP5012PWR.h
 *
 * Created: 22/06/2021 20:07:19
 *  Author: Anon
 */ 


#ifndef LP5012PWR_H_
#define LP5012PWR_H_

#define LP5012_ADDR_WRITE            0x28
#define LP5012_ADDR_READ             0x29

/// REGISTER DEFINITIONS
#define LP5012_DEVICE_CONFIG0        0x00
#define LP5012_DEVICE_CONFIG1        0x01
#define LP5012_LED_CONFIG0           0x02
#define LP5012_BANK_BRIGHTNESS       0x03
#define LP5012_BANK_A_COLOR          0x04
#define LP5012_BANK_B_COLOR          0x05
#define LP5012_BANK_C_COLOR          0x06

/// PREDEFINED REG CONFIGS
#define LP5012_DEV_CFG0_DEFAULT      0x40 // [7]=0, [6]=1 (CHIP_EN), [5:0]=0
#define LP5012_DEV_CFG1_DEFAULT		 0x26 // [7:6]=0, [5]=1 (LOG_SCALE_EN), [4]=0 (!POWER_SAVE_EN), [3]=0 (!AUTO_INCR_EN), [2]=1 (PWM_DITHERING_EN), [1]=1 (MAX_CURRENT_OPTION), [0]=0 (!LED_GLOBAL_OFF)

/// BIT DEFINITIONS
#define LP5012_DEV_CFG1_CHIP_EN      0x06

uint8_t setup_LP5012();

/*
void i2c_read()
{
	SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_WRITE;
	
	if(SERCOM0->I2CM.STATUS.bit.BUSSTATE == 0x2 && !SERCOM0->I2CM.STATUS.bit.RXNACK) // The MCU has the bus and we have received an ACK, we can now send data
	{
		SERCOM0->I2CM.DATA.reg = LP5012_DEVICE_CONFIG0;
		while(SERCOM0->I2CM.STATUS.bit.RXNACK);
		SERCOM0->I2CM.DATA.reg = (1 << LP5012_DEV_CFG1_CHIP_EN);
	}
	
	SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_WRITE;
	
	if(SERCOM0->I2CM.STATUS.bit.BUSSTATE == 0x2 && !SERCOM0->I2CM.STATUS.bit.RXNACK) // The MCU has the bus and we have received an ACK, we can now send data
	{
		SERCOM0->I2CM.DATA.reg = LP5012_DEVICE_CONFIG0;
		SERCOM0->I2CM.CTRLB.bit.CMD = 0x1; // repeated start
		
		SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_READ;
		
		if(SERCOM0->I2CM.DATA.reg == 0x06)
		{
			GPIO_output(PORT_PA23, true);
		}
		SERCOM0->I2CM.CTRLB.bit.CMD = 0x3; // STOP condition
	}
	
	SERCOM0->I2CM.ADDR.bit.ADDR = LP5012_ADDR_WRITE;
	
	if(SERCOM0->I2CM.STATUS.bit.BUSSTATE == 0x2 && !SERCOM0->I2CM.STATUS.bit.RXNACK) // The MCU has the bus and we have received an ACK, we can now send data
	{
		SERCOM0->I2CM.DATA.reg = LP5012_BANK_BRIGHTNESS;
		while(SERCOM0->I2CM.STATUS.bit.RXNACK);
		SERCOM0->I2CM.DATA.reg = 0;
	}
	
	//GPIO_output(PORT_PA23, true);

}
*/

#endif /* LP5012PWR_H_ */