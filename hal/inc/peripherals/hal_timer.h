#ifndef HAL_TIMER_H
#define HAL_TIMER_H

/** \file
 *
 * File containing definitions for timer related functions.
 * 
 * \warning Currently only supports a simple delay.
 */

#include <stdint.h>

#include "hal_result.h"

/** Timer 'tick' event call-back declaration. */
typedef void (*hal_timer_event_cb_t)(void);

/** Structure representing timer initialisation. */
typedef struct hal_timer_init
{
    uint16_t             period;    /*!< The period of the timer in ms. */
    hal_timer_event_cb_t call_back; /*!< Callback for timer tick. */

} hal_timer_init_t;

/** Initialise a timer peripheral
 *
 *  \param[in] init_struct Timer initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_timer_init()` call being made.
 *  \retval #HAL_ERROR_PARAM_ERROR Initialisation failed due to a parameter error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_timer_init(hal_timer_init_t *init_struct);

/** Initialise clocks used by the timer peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_timer_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_timer_clock_init(void);

/** Teardown a previously initialised timer peripheral.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_timer_init()` call not being made.
 */
hal_result_t hal_timer_teardown(void);

/** Teardown clocks used by the timer peripheral.
 *
 *  \retval #HAL_SUCCESS Initialiqsation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_timer_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_timer_clock_teardown(void);

/** Blocking delay for a specified length of time.
 *
 *  \param[in] ms The length of delay in ms.
 *  
 *  \retval #HAL_SUCCESS Delay was successful.
 *  \retval #HAL_ERROR_REJECTED Delay failed due to a previous `hal_timer_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_timer_delay(uint16_t ms);

/** Get the current 'tick' count of the timer.
 *  
 *  \retval The current tick value of the running timer.
 */
uint32_t hal_timer_get_tick(void);

/** Start a previously initialised timer.
 *  
 *  \retval #HAL_SUCCESS Timer was successfully started.
 *  \retval #HAL_ERROR_REJECTED Delay failed due to a previous `hal_timer_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_timer_start(void);

/** Stop a previously initialised timer.
 *  
 *  \retval #HAL_SUCCESS Timer was successfully stopped.
 *  \retval #HAL_ERROR_REJECTED Delay failed due to a previous `hal_timer_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_timer_stop(void);

#endif /* HAL_TIMER_H */
