#ifndef HAL_I2C_H
#define HAL_I2C_H

/** \file
 * 
 * File containing definitions for I2C functions.
 * 
 * \warning Currently only supports host mode.
 */

#include "../hal_result.h"

/** Initialise I2C.
 *
 *  \param[in] init_struct I2C initialisation structure.
 * 
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_i2c_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_i2c_init(hal_i2c_init_t init_struct);

/** Initialise I2C clocks.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_i2c_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_i2c_clock_init(void);

/** Teardown previously intialised i2c clocks.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due a previous `hal_i2c_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Teardown failed due to a peripheral error.
 */
hal_result_t hal_i2c_clock_teardown(void);

/** Teardown resources set up by `hal_i2c_init()`.
 * 
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_i2c_init()` call not being made.
 */
hal_result_t hal_i2c_teardown(void);

#endif