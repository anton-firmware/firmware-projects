/** \file
 *
 * Implementation for HAL USB peripheral.
 * 
 * \warning Intended to be used with the TinyUSB library for actual USB stack implementation,
 *          the functions below will only implement setting up the necessary clocks to allow the USB
 *          peripheral to function.
 */

#include <stdbool.h>
#include <stdint.h>

#include "hal_usb.h"
#include "hal_result.h"
#include "sam.h"

static bool external_clock = false;
static bool initialised = false;

static hal_result_t initialise_internal_usb_clock(void)
{
    
}

static hal_result_t initialise_external_usb_clock(void)
{
    
}

hal_result_t hal_usb_init(hal_usb_init_t *init_struct)
{
    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    if (init_struct)
    {
        external_clock = init_struct->external_clock;
        initialised = true;
        result = HAL_SUCCESS;
    }

    return result;
}

hal_result_t hal_usb_clock_init(void)
{
    hal_result_t result = HAL_ERROR_REJECTED;

    if (initialised)
    {
        PM->AHBMASK.reg |= PM_AHBMASK_USB;

        if (external_clock)
        {
            result = initialise_external_usb_clock();
        }
        else
        {
            result = initialise_internal_usb_clock();
        }
    }

    return result;
}

hal_result_t hal_usb_teardown(void)
{
    hal_result_t result = HAL_ERROR_REJECTED;

    if (initialised)
    {
        PM->AHBMASK.reg &= ~PM_AHBMASK_USB;

        initialised = false;
        result = HAL_SUCCESS;
    }

    return result;
}

hal_result_t hal_usb_clock_teardown(void)
{

}
