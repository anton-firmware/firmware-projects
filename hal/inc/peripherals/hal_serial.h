#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

/** \file
 *
 * File containing definitions for serial (UART) functions.
 */

#include "../hal_result.h"

typedef enum hal_serial_mode
{
    HAL_SERIAL_MODE_RX,    /*!< Serial RX Only mode. */
    HAL_SERIAL_MODE_TX,    /*!< Serial TX Only modee. */
    HAL_SERIAL_MODE_RX_TX, /*!< Serial RX/TX mode. */

} hal_serial_mode_t;

typedef enum hal_serial_stop_bits
{
    HAL_SERIAL_STOP_BITS_ONE, /*!< Serial 1 stop bit. */
    HAL_SERIAL_STOP_BITS_TWO, /*!< Serial 2 stop bits. */

} hal_serial_stop_bits_t;

typedef enum hal_serial_parity_bits
{
    HAL_SERIAL_PARITY_BITS_NONE, /*!< Serial no parity bits. */
    HAL_SERIAL_PARITY_BITS_ONE,  /*!< Serial one parity bit. */

} hal_serial_parity_bits_t;


#endif /* HAL_SERIAL_H */
