#include <stddef.h>
#include <stdint.h>

#include "hal_core_unique_id.h"

/* See 9.6 Serial Number Atmel-42363H-SAM-D11-Datasheet_09/2016 */
#define SERIAL_NUMBER_LEN 16u

/* See 9.6 Serial Number Atmel-42363H-SAM-D11-Datasheet_09/2016
 * Each device has a unique 128-bit serial number which is a concatenation of four 32-bit words 
 * four 32-bit words contained at the following addresses. 
 */
#define SERIAL_NUMBER_WORD_0 ((volatile const uint32_t *)(0x0080A00C))
#define SERIAL_NUMBER_WORD_1 ((volatile const uint32_t *)(0x0080A040))
#define SERIAL_NUMBER_WORD_2 ((volatile const uint32_t *)(0x0080A044))
#define SERIAL_NUMBER_WORD_3 ((volatile const uint32_t *)(0x0080A048))

uint8_t hal_unique_id_get_size(void)
{
    return SERIAL_NUMBER_LEN;
}

hal_result_t hal_unique_id_get_id(uint32_t *buf, uint8_t len)
{
    hal_result_t result;

    if (buf == NULL || len == 0)
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (len != SERIAL_NUMBER_LEN)
    {
        result = HAL_ERROR_REJECTED;
    }
    else
    {
        buf[0] = *SERIAL_NUMBER_WORD_0;
        buf[1] = *SERIAL_NUMBER_WORD_1;
        buf[2] = *SERIAL_NUMBER_WORD_2;
        buf[3] = *SERIAL_NUMBER_WORD_3;
        
        result = HAL_SUCCESS;
    }
    
    return result;
}
