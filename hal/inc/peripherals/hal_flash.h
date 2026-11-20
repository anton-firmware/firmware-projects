#ifndef HAL_FLASH_H
#define HAL_FLASH_H

#include <stdint.h>

/** \file
 *
 * File containing definitions for GPIO functions.
 */

#include "hal_result.h"

/** Write 
 *
 *  \param[in] init_struct Pointer to a GPIO initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_PARAM_ERROR An invalid parameter was detected.
 *  \retval #HAL_ERROR_REJECTED The \c addr was not aligned correctly for the target device.
 */
hal_result_t hal_flash_write_data(const uint8_t *source, uint8_t len, uint32_t addr);

#endif /* HAL_FLASH_H */
