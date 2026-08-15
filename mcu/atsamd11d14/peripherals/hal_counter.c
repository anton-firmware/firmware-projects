/** \file
 *
 * File containing implementation for 16-bit counter related functions.
 */

#include <stdint.h>

#include "sam.h"

#include "hal_counter.h"
#include "hal_result.h"

#define TOP_VALUE (46874 / 2)

static hal_counter_event_cb_t hal_cb;

void TC1_Handler(void)
{
	if (TC1->COUNT16.INTFLAG.bit.MC0 && hal_cb != 0)
	{
		hal_cb();
	}

	TC1->COUNT16.INTFLAG.bit.MC0 = 1;
}

hal_result_t hal_counter_init(hal_counter_init_t *init_struct)
{
	hal_result_t result = HAL_ERROR_PARAM_ERROR;
	
	if (init_struct)
	{
		if (init_struct->call_back != 0)
		{
			hal_cb = init_struct->call_back;
		}
		
		TC1->COUNT16.CTRLA.bit.PRESCALER = 0x07; // Use 1024 pre-scaler.
		TC1->COUNT16.CTRLA.bit.WAVEGEN = 0x1; // Match frequency wave generation.
		TC1->COUNT16.CTRLA.bit.PRESCSYNC = 1; // Reload/reset on next prescaler clock.
		TC1->COUNT16.INTENSET.bit.MC0 = 1;
		TC1->COUNT16.CC[0].reg = TOP_VALUE;
		
		NVIC_EnableIRQ(TC1_IRQn);
	}
	
	return result;
}

hal_result_t hal_counter_clock_init(void)
{
	PM->APBCMASK.reg |= PM_APBCMASK_TC1;
	
	GCLK->GENDIV.reg  = GCLK_GENDIV_ID(3) | GCLK_GENDIV_DIV(0);
	
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY); 
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(3)       |
	                    GCLK_GENCTRL_SRC_DFLL48M |
	                    GCLK_GENCTRL_IDC         |
						GCLK_GENCTRL_GENEN;
						
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_TC1_TC2 | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(3);
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
	
	return HAL_SUCCESS;
}

hal_result_t hal_counter_teardown(void)
{
    return HAL_ERROR_NOT_IMPLEMENTED;
}

hal_result_t hal_counter_clock_teardown(void)
{
    return HAL_ERROR_NOT_IMPLEMENTED;
}

hal_result_t hal_counter_delay(uint16_t ms)
{
    return HAL_ERROR_NOT_IMPLEMENTED;
}

uint16_t hal_counter_get_count(void)
{
    return TC1->COUNT16.CC[0].reg;
}

hal_result_t hal_counter_start(void)
{
    TC1->COUNT16.CTRLA.bit.ENABLE = 1;
	while(TC1->COUNT16.STATUS.bit.SYNCBUSY);
	
	return HAL_SUCCESS;
}

hal_result_t hal_counter_stop(void)
{
    return HAL_ERROR_NOT_IMPLEMENTED;
}

void hal_counter_change_compare_value(uint16_t new_val)
{
	TC1->COUNT16.CC[0].reg = new_val;
}

