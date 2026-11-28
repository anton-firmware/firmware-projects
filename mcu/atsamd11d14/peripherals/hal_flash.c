/** \file
 *
 * File containing implementation for flash related functions for the SAMD11.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sam.h"

#include "hal_core_interrupts.h"
#include "hal_flash.h"
#include "hal_result.h"

#define PAGE_NUMBER    256u
#define PAGE_LEN_BYTES 64u

#define ROW_LEN_BYTES (PAGE_LEN_BYTES * 4u)

hal_result_t hal_flash_write_data(const uint32_t *data, uint8_t len, uint32_t *addr)
{
    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    if ((data != NULL) && (len !=0) && !(len % PAGE_LEN_BYTES) && (addr != NULL) && (len <= ROW_LEN_BYTES))
    {
        const uint32_t* start_data = data;

        uint8_t pages = (len / PAGE_LEN_BYTES);
        
        hal_interrupts_disable();

        /* See 21.8.8 Address - Atmel | SMART SAM D11 [DATASHEET]
         * For some god-foresaken reason, the NVM operates on "half-word" pairs, so we
         * need to divide the address by 2 before slapping it into the NVM for a row erase.*/
        NVMCTRL->ADDR.reg = ((uint32_t)addr >> 1u);

        NVMCTRL->CTRLA.reg = (NVMCTRL_CTRLA_CMD_ER | NVMCTRL_CTRLA_CMDEX_KEY);

        while (NVMCTRL->INTFLAG.bit.READY == 0);

        /* Manual write, we will issue the command through CMD in CTRLA. */
        NVMCTRL->CTRLB.bit.MANW = 1;

        do 
        {
            for (uint8_t i = 0; i < PAGE_LEN_BYTES; i += 4)
            {
                *addr++ = *start_data++;
            }

            NVMCTRL->CTRLA.reg = (NVMCTRL_CTRLA_CMD_WP | NVMCTRL_CTRLA_CMDEX_KEY);

            while (NVMCTRL->INTFLAG.bit.READY == 0);
        } 
        while (--pages);

        hal_interrupts_enable();

        result = HAL_SUCCESS;
    }
    
    return result;
}
