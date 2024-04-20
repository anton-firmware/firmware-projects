#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

/** \file
 *
 * File containing definitions for serial (UART) functions.
 * 
 * \warning The current implementation assumes only one peripheral. 
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

/** Structure representing serial initialisation. */
typedef struct hal_serial_init
{
    hal_serial_mode_t        mode;        /*!< Serial mode. */
    hal_serial_stop_bits_t   stop_bits;   /*!< Serial stop bits. */
    hal_serial_parity_bits_t parity_bits; /*!< Serial parity bits. */

} hal_serial_init_t;

/** Initialise a serial peripheral
 *
 *  \param[in] init_struct Serial initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_serial_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_serial_init(hal_serial_init_t init_struct);

/** Initialise clocks used by the serial peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_serial_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_serial_clock_init(void);

/** Teardown a previously initialised serial peripheral.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_serial_init()` call not being made.
 */
hal_result_t hal_serial_teardown(void);

/** Teardown clocks used by the serial peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_serial_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_serial_clock_teardown(void);

#endif /* HAL_SERIAL_H */
