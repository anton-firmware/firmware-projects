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

hal_result_t hal_serial_init(hal_serial_init_t *init_struct)
{
    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    if (!init_struct)
    {
        // Do nothing, invalid init structure.
    }
    else if (sercom_usart_enabled)
    {
        // Trying to initialise already initialised USART.
        result = HAL_ERROR_REJECTED;
    }
    else 
    {
        switch (init_struct->mode)
        {
            case HAL_SERIAL_MODE_RX:
                // TODO: SERCOM[0] RX Only.
                break;
            case HAL_SERIAL_MODE_TX:
                // TODO: SERCOM[0] TX Only.
                break;
            case HAL_SERIAL_MODE_RX_TX:
                // TODO: SERCOM[0] RX/TX.
                break;
            default:
                // Cry, invalid USART mode.
                break;
        }

        switch (init_struct->stop_bits)
        {
            case HAL_SERIAL_STOP_BITS_ONE:
                // TODO: One stop bit.
                break;
            case HAL_SERIAL_STOP_BITS_TWO:
                // TODO: Two stop bits.
                break;
            default:
                // Cry, invalid stop bits.
                break;
        }

        switch (init_struct->parity_bits)
        {
            case HAL_SERIAL_PARITY_BITS_NONE:
                // TODO: No parity bits.
                break;
            case HAL_SERIAL_PARITY_BITS_ONE:
                // TODO: One parity bit.
                break;
            default:
                // Cry, invalid parity bits.
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
                // Cry, invalid baud rate.
                break;
        }
        
        // TODO, callback initialisation.

        sercom_usart_enabled = true;
    }

    return result;
}

hal_result_t hal_serial_clock_init()
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    return result;
}

hal_result_t hal_serial_teardown()
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    return result;    
}
