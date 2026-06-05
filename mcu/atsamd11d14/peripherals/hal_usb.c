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
    uint16_t clk_ctl_reg_value = 0;
    uint32_t clk_gen_reg_value = 0;

    /* USB Clock Recovery mode can be used to create the 48MHz USB clock from the USB Start Of Frame (SOF). 
     * See USB Clock Recovery Mode Page 154 SMART SAM D11 Datasheet. */

    /* Set Generic Clock Generator 1 to be fed from DFLL48M output
    */

    /* Set the USB core clock to be Generic Clock Generator 0 (Internal 8MHz oscilator). 
     * Note: On reset, the OSC8M is fed through a divide by 8 step, so this clock is actually 1MHz. 
     */
    clk_ctl_reg_value |= (GCLK_CLKCTRL_ID_USB_CORE | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK1);

    GCLK->CLKCTRL.reg = clk_ctl_reg_value; 

    /* Wait for syncronisation. */
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
}

static hal_result_t initialise_external_usb_clock(void)
{
    return HAL_ERROR_NOT_IMPLEMENTED;
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
