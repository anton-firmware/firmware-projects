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
    /* Set NVM wait states for 48MHz operation as required by electrical characteristics */
    NVMCTRL->CTRLB.bit.RWS = 1;
	
    /* 2. Set GCLK1 to use OSC8M as reference for DFLL
     * (don't touch GCLK0 until DFLL is locked) */
    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(1)     |
                        GCLK_GENCTRL_SRC_OSC8M  |
                        GCLK_GENCTRL_IDC         |
                        GCLK_GENCTRL_GENEN;
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    /* 3. Route GCLK1 to DFLL48 reference input */
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_DFLL48 |
                        GCLK_CLKCTRL_CLKEN      |
                        GCLK_CLKCTRL_GEN(1);
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    /* 4. Extract factory DFLL coarse calibration */
    uint32_t coarse_cal = ((*((volatile uint32_t *)0x00806024)) & (0x3F << 26)) >> 26;

    /* 5. See errata reference 9905 - The DFLL clock must be requested before being configured otherwise a write access to a DFLL register can freeze the device */
    SYSCTRL->DFLLCTRL.bit.ONDEMAND = 0;

    /* 6. Inject coarse calibration */
    SYSCTRL->DFLLVAL.reg = SYSCTRL_DFLLVAL_COARSE(coarse_cal);
    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0);

    /* 7. Set multiplier: 48MHz / 1MHz = 1 */
    SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_MUL(48)   |
                           SYSCTRL_DFLLMUL_CSTEP(1)  |
                           SYSCTRL_DFLLMUL_FSTEP(1);
    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0);

    /* 8. Enable DFLL in closed loop mode, wait for lock */
    SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_MODE     |
                            SYSCTRL_DFLLCTRL_WAITLOCK |
                            SYSCTRL_DFLLCTRL_ENABLE;
    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0);

    /* 9. Wait for coarse and fine lock */
    while ((SYSCTRL->PCLKSR.reg & (SYSCTRL_PCLKSR_DFLLLCKC | SYSCTRL_PCLKSR_DFLLLCKF))
           != (SYSCTRL_PCLKSR_DFLLLCKC | SYSCTRL_PCLKSR_DFLLLCKF));

    /* 10. Switch GCLK0 (system/CPU clock) to DFLL48M @ 48MHz */
    GCLK->GENDIV.reg  = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(0);
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0)      |
                        GCLK_GENCTRL_SRC_DFLL48M |
                        GCLK_GENCTRL_IDC          |
                        GCLK_GENCTRL_GENEN;
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    /* 11. Route GCLK0 to USB peripheral */
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_USB |
                        GCLK_CLKCTRL_CLKEN   |
                        GCLK_CLKCTRL_GEN(0);
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    return HAL_SUCCESS;
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
