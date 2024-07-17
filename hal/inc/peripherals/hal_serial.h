#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

/** \file
 *
 * File containing definitions for serial (UART) functions.
 * 
 * \warning The current implementation assumes only one peripheral. 
 */

#include "hal_result.h"

typedef enum hal_serial_mode
{
    HAL_SERIAL_MODE_RX,    /*!< Serial RX Only mode. */
    HAL_SERIAL_MODE_TX,    /*!< Serial TX Only mode. */
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

typedef enum hal_serial_baud_rate
{
    HAL_SERIAL_BAUD_RATE_4800,   /*!< Serial baud rate 4800bps. */
    HAL_SERIAL_BAUD_RATE_9600,   /*!< Serial baud rate 9600bps. */
    HAL_SERIAL_BAUD_RATE_115200, /*!< Serial baud rate 115200bps. */

} hal_serial_baud_rates_t;

/** Read-event callback declaration.
 *
 * \param[out] buf Byte that was read.
 */
typedef void (*hal_serial_read_cb_t)(uint8_t buf);

/** Write-event callback declaration.
 *
 * \param[in] bytes The number of bytes written.
 */
typedef void (*hal_serial_write_cb_t)(const uint8_t bytes);

/** Structure representing serial initialisation. */
typedef struct hal_serial_init
{
    hal_serial_mode_t        mode;           /*!< Serial mode. */
    hal_serial_stop_bits_t   stop_bits;      /*!< Serial stop bits. */
    hal_serial_parity_bits_t parity_bits;    /*!< Serial parity bits. */
    hal_serial_baud_rates_t  baud_rate;      /*!< Serial baud rate. */
    hal_serial_read_cb_t     read_event_cb;  /*!< Serial read callback. */
    hal_serial_write_cb_t    write_event_cb; /*!< Serial write callback. */
    
    uint8_t                  *tx_buf;        /*!< Pointer to transmit buffer. */
    uint8_t                   tx_buf_len;    /*!< Length (in bytes) of transmit buffer. */

} hal_serial_init_t;

/** Initialise a serial peripheral
 *
 *  \param[in] init_struct Serial initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_serial_init()` call being made.
 *  \retval #HAL_ERROR_PARAM_ERROR Initialisation failed due to a parameter error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_serial_init(hal_serial_init_t *init_struct);

/** Initialise clocks used by the serial peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_serial_clock_init()` call being made.
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
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_serial_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_serial_clock_teardown(void);

/** Transmit a number of bytes over the serial periperhal in blocking mode.
 * 
 * \param[in] tx Pointer to data to transmit.
 * \param[in] len Number of bytes to transmit.
 * 
 * \retval #HAL_SUCCESS The data were successfully transmitted.
 * \retval #HAL_ERROR_REJECTED Transmission failed due to a previous `hal_serial_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Transmission failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Transmission failed due to a peripheral error.
 */
hal_result_t hal_serial_transmit_blocking(const uint8_t *tx, const uint8_t len);

/** Transmit a number of bytes over the serial periperhal in non blocking mode.
 * 
 * \param[in] tx Pointer to data to transmit.
 * \param[in] len Number of bytes to transmit.
 * 
 * \retval #HAL_SUCCESS The data were successfully transmitted.
 * \retval #HAL_ERROR_REJECTED Transmission failed due to a previous `hal_serial_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Transmission failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Transmission failed due to a peripheral error.
 */
hal_result_t hal_serial_transmit_non_blocking(const uint8_t *tx, const uint8_t len);

/** Receive a number of bytes over the serial periperhal in blocking mode.
 * 
 * \param[in] tx Pointer to buffer into which to receive data.
 * \param[in] len Number of bytes to receive.
 * 
 * \retval #HAL_SUCCESS The data were successfully received.
 * \retval #HAL_ERROR_REJECTED Reception failed due to a previous `hal_serial_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Reception failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Reception failed due to a peripheral error.
 */
hal_result_t hal_serial_receive_blocking(uint8_t *tx, const uint8_t len);

/** Receive a number of bytes over the serial periperhal in non blocking mode.
 * 
 * \param[in] tx Pointer to buffer into which to receive data.
 * \param[in] len Number of bytes to receive.
 * 
 * \retval #HAL_SUCCESS The data were successfully transmitted.
 * \retval #HAL_ERROR_REJECTED Reception failed due to a previous `hal_serial_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Reception failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Reception failed due to a peripheral error.
 */
hal_result_t hal_serial_receive_non_blocking(uint8_t *tx, const uint8_t len);

#endif /* HAL_SERIAL_H */
