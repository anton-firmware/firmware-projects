#include <stdbool.h>

#include "hal_serial.h"
#include "sam.h"

/** \file
 *
 * Implementation for HAL Serial peripheral.
 * 
 * \warning The current implementation only works for SERCOM[0].
 */

static bool sercom_usart_enabled;

/** Function(s) to wait for syncronization.
 *  
 * See page 451 - Atmel SAMD11 reference manual.
 * See page 472, 25.8.9, Synchronization Busy register.
 * 
 * This is required due to the asynchronicity between CLK_SERCOMx_APB and GCLK_SERCOMx_CORE.
 */
static inline void wait_for_sync_swrst(void)
{
    while (SERCOM0->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_SWRST);
}

static inline void wait_for_sync_enable(void)
{
    while (SERCOM0->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_ENABLE);
}

static inline void wait_for_sync_ctrl_b(void)
{
    while (SERCOM0->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_CTRLB);
}

hal_result_t hal_serial_init(hal_serial_init_t *init_struct)
{
    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    if (!init_struct)
    {
        /* Do nothing, invalid init structure. */
    }
    else if (sercom_usart_enabled)
    {
        /* Trying to initialise already initialised USART. */
        result = HAL_ERROR_REJECTED;
    }
    else 
    {
        /* USART with internal clock. */
        SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_MODE(0x1);

        switch (init_struct->mode)
        {
            case HAL_SERIAL_MODE_RX:
                SERCOM0->USART.CTRLB.reg |= SERCOM_USART_CTRLB_RXEN;
                break;
            case HAL_SERIAL_MODE_TX:
                SERCOM0->USART.CTRLB.reg |= SERCOM_USART_CTRLB_TXEN;
                break;
            case HAL_SERIAL_MODE_RX_TX:
                SERCOM0->USART.CTRLB.reg |= (SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_RXEN);
                break;
            default:
                /* Cry, invalid USART mode. */
                break;
        }

        switch (init_struct->stop_bits)
        {
            case HAL_SERIAL_STOP_BITS_ONE:
                SERCOM0->USART.CTRLB.reg &= ~SERCOM_USART_CTRLB_SBMODE;
                break;
            case HAL_SERIAL_STOP_BITS_TWO:
                SERCOM0->USART.CTRLB.reg |= SERCOM_USART_CTRLB_SBMODE;
                break;
            default:
                /* Cry, invalid stop bits. */
                break;
        }

        /* This driver currently only supports even parity. */
        switch (init_struct->parity_bits)
        {
            case HAL_SERIAL_PARITY_BITS_NONE:
                SERCOM0->USART.CTRLA.reg &= ~SERCOM_USART_CTRLA_FORM(0x1);
                break;
            case HAL_SERIAL_PARITY_BITS_ONE:
                /* FORM 0x1 = USART frame with parity, see Table 25-6, ATSAMD11 reference manual.*/
                SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_FORM(0x1);
                break;
            default:
                /* Cry, invalid parity bits. */
                break;
        }

        switch (init_struct->baud_rate)
        {
            case HAL_SERIAL_BAUD_RATE_4800:
                // TODO: 4800 baud.
                break;
            case HAL_SERIAL_BAUD_RATE_9600:
                // TODO: 9600 baud.
                break;
            case HAL_SERIAL_BAUD_RATE_115200:
                // TODO: 115200 baud.
                break;
            default:
                /* Cry, invalid baud rate. */
                break;
        }
        
        // TODO, callback initialisation.

        SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;

        wait_for_sync_enable();

        sercom_usart_enabled = true;
    }

    return result;
}

hal_result_t hal_serial_clock_init()
{
    /** Enable APB clock for SERCOM0. */
    PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;

    return HAL_SUCCESS;
}

hal_result_t hal_serial_teardown()
{
    /** Disable APB clock for SERCOM0. */
    PM->APBCMASK.reg &= ~PM_APBCMASK_SERCOM0;

    return HAL_SUCCESS;    
}
