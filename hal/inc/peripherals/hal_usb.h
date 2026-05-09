#ifndef HAL_USB_H
#define HAL_USB_H

/** \file
 *
 * File containing definitions for USB related functions.
 * 
 * \warning Intended to be used with the TinyUSB library for actual USB stack implementation,
 *          the functions below will only implement setting up the necessary clocks to allow the USB
 *          peripheral to function.
 */

#include <stdint.h>
#include <stdbool.h>

#include "hal_result.h"

/** Structure representing USB initialisation. */
typedef struct hal_usb_init
{
       bool external_clock; /*!< Whether or not the USB peripheral uses an external clock. */
} hal_usb_init_t;

/** Initialise a USB peripheral.
 *
 *  \param[in] init_struct USB initialisation structure.
 * 
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_usb_init()` call being made.
 *  \retval #HAL_ERROR_PARAM_ERROR Initialisation failed due to a parameter error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_usb_init(hal_usb_init_t *init_struct);

/** Initialise clocks used by the USB peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_usb_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_usb_clock_init(void);

/** Teardown a previously initialised USB peripheral.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_usb_init()` call not being made.
 */
hal_result_t hal_usb_teardown(void);

/** Teardown clocks used by the USB peripheral.
 *
 *  \retval #HAL_SUCCESS Initialiqsation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_usb_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_usb_clock_teardown(void);

#endif /* HAL_USB_H */
