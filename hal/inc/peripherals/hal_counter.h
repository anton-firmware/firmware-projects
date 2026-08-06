#ifndef HAL_COUNTER_H
#define HAL_COUNTER_H

/** \file
 *
 * File containing definitions for 16-bit counter related functions.
 */

#include <stdint.h>

#include "hal_result.h"

/** Counter overflow event call-back declaration. */
typedef void (*hal_counter_event_cb_t)(void);

/** Structure representing counter initialisation. */
typedef struct hal_counter_init
{
    uint16_t             period;    /*!< The period of the counter in ms. */
    hal_counter_event_cb_t call_back; /*!< Callback for counter tick. */

} hal_counter_init_t;

/** Initialise a counter peripheral
 *
 *  \param[in] init_struct Counter initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_counter_init()` call being made.
 *  \retval #HAL_ERROR_PARAM_ERROR Initialisation failed due to a parameter error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_counter_init(hal_counter_init_t *init_struct);

/** Initialise clocks used by the counter peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_counter_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_counter_clock_init(void);

/** Teardown a previously initialised counter peripheral.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_counter_init()` call not being made.
 */
hal_result_t hal_counter_teardown(void);

/** Teardown clocks used by the counter peripheral.
 *
 *  \retval #HAL_SUCCESS Initialiqsation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_counter_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_counter_clock_teardown(void);

/** Blocking delay for a specified length of time.
 *
 *  \param[in] ms The length of delay in ms.
 *  
 *  \retval #HAL_SUCCESS Delay was successful.
 *  \retval #HAL_ERROR_REJECTED Delay failed due to a previous `hal_counter_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_counter_delay(uint16_t ms);

/** Get the current 'tick' count of the counter.
 *  
 *  \retval The current tick value of the running counter.
 */
uint32_t hal_counter_get_tick(void);

/** Start a previously initialised counter.
 *  
 *  \retval #HAL_SUCCESS Counter was successfully started.
 *  \retval #HAL_ERROR_REJECTED Delay failed due to a previous `hal_counter_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_counter_start(void);

/** Stop a previously initialised counter.
 *  
 *  \retval #HAL_SUCCESS Counter was successfully stopped.
 *  \retval #HAL_ERROR_REJECTED Delay failed due to a previous `hal_counter_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_counter_stop(void);

#endif /* HAL_COUNTER_H */
