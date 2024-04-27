#ifndef HAL_H
#define HAL_H

#include "hal_result.h"

/**
 * \defgroup hal Hardware abstraction layer (HAL).
 * \{
 */

/** Perform initialisation needed for MCU functionality. 
 *
 *  \warning This function must be called before using any other HAL function.
 * 
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_init()` call being made.
 *  \retval #HAL_ERROR_DEVICE_ERROR Initialisation failed due to to a device error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_init(void);

/** Teardown resources set up by `hal_init()`.
 * 
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_init()` call not being made.
 */
hal_result_t hal_teardown(void);

/** \} hal group */

#endif /* HAL_H */
