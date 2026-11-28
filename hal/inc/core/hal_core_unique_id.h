#ifndef HAL_CORE_UNIQUE_ID_H
#define HAL_CORE_UNIQUE_ID_H

/** \file
 * 
 * File containing functions related to reading the unique ID (if present) of the MCU.
 */

#include <stdint.h>

#include "hal_result.h"

/** Gets the length (in bytes) of the unique ID. 
 *
 * \returns The unique ID length in bytes, 0 if this MCU does not have a unique ID. 
 */
uint8_t hal_unique_id_get_size(void);

/** Copies the unique ID into a buffer provided by the user.
 *
 *  \param[in] buf The buffer into which the unqiue ID will be copied.
 *  \param[in] len The length of the buffer in bytes.
 * 
 *  \retval #HAL_SUCCESS The data were successfully copied.
 *  \retval #HAL_ERROR_PARAM_ERROR An invalid parameter was detected.
 *  \retval #HAL_ERROR_REJECTED The \c len was not big enough to fit the unique ID.
 */
hal_result_t hal_unique_id_get_id(uint32_t *buf, uint8_t len);

#endif /* HAL_CORE_INTERRUPTS_H */
