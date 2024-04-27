#ifndef HAL_CORE
#define HAL_CORE

/** \file
 * 
 * File containing functions related to core clock initialisation.
 */

#include "../hal_result.h"

typedef enum CLOCK_TYPE
{
    CLOCK_INTERNAL, /*!< Internal clock. (e.g. PLL, HSI) */
    CLOCK_EXTERNAL, /*!< External clock. */

} clock_type_t; 

/** Initialise non-peripheral related MCU clocks.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_clock_init()` call being made.
 *  \retval #HAL_ERROR_DEVICE_ERROR Initialisation failed due to a device error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_clock_init(void);

/** Teardown resources set up by `hal_clock_init()`.
 * 
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_clock_init()` call not being made.
 */
hal_result_t hal_clock_teardown(void);

/** Returns the current frequency of the system clock.
 * 
 *  \return The frequency of the system clock in Hz. 
 */
uint32_t hal_get_system_clock_frequency(void);

/** Returns the type of the system clock.
 * 
 *  \retval #CLOCK_INTERNAL An internal clock is being used as the system clock.
 *  \retval #CLOCK_EXTERNAL An external clock is being used as the system clock.
 */
clock_type_t hal_get_system_clock_type(void);

#endif /* HAL_CORE */
