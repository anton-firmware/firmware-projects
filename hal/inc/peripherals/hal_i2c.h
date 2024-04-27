#ifndef HAL_I2C_H
#define HAL_I2C_H

/** \file
 *
 * File containing definitions for I2C functions.
 *
 * \warning Currently only supports host mode.
 */

#include "../hal_result.h"

typedef enum hal_i2c_speeds
{
    HAL_I2C_STANDARD,  /*!< I2C standard 100KHz. */
    HAL_I2C_FAST,      /*!< I2C fast 400KHz. */
    HAL_I2C_FAST_PLUS, /*!< I2C fast plus 1MHz. */
    HAL_I2C_HIGH_SPEED /*!< I2C high speed 3.4MHz. */

} hal_i2c_speed_t;

/** Structure representing I2C initialisation. */
typedef struct hal_i2c_init
{
    hal_i2c_peripheral_id_t peripheral_id; /*!< I2C peripheral ID. */
    hal_i2c_speed_t         speed;         /*!< I2C peipheral speed. */

} hal_i2c_init_t;

/** ID of the I2C peripheral. */
typedef uint8_t hal_i2c_peripheral_id_t;

/** Read-event callback declaration.
 *
 * \param[out] buf Pointer to data buffer.
 *
 * \return The number of bytes read, 0 otherwise.
 */
typedef uint8_t (*hal_i2c_read_cb_t)(uint8_t *buf);

/** Write-event callback declaration.
 *
 *  \return The number of bytes written, 0 otherwise.
 */
typedef uint8_t (*hal_i2c_write_cb_t)(void);

/** Initialise I2C.
 *
 *  \param[in] init_struct I2C initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_i2c_init()` call being made.
 *  \retval #HAL_ERROR_PARAM_ERROR Transmission failed due to a parameter error.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_i2c_init(hal_i2c_init_t init_struct);

/** Initialise I2C clocks.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_i2c_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_i2c_clock_init(void);

/** Teardown previously intialised I2C clocks.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_i2c_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Teardown failed due to a peripheral error.
 */
hal_result_t hal_i2c_clock_teardown(void);

/** Teardown resources set up by `hal_i2c_init()`.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_i2c_init()` call not being made.
 */
hal_result_t hal_i2c_teardown(void);

/** Read a number of \c bytes from a target's \c reg given by \c address in blocking mode.
 *
 * \param[in] id I2C host peripheral ID.
 * \param[in] address Address of the target to read data from.
 * \param[in] reg Register address on the target to read data from.
 * \param[in] bytes Number of bytes to read from the target.
 * \param[out] buf The buffer into which data from the target are to be stored.
 * 
 * \retval #HAL_SUCCESS Reading was successful.
 * \retval #HAL_ERROR_REJECTED Reading failed due to a previous `hal_i2c_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Reading failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Reading failed due to a peripheral error.
 */
hal_result_t hal_i2c_host_read_blocking(hal_i2c_peripheral_id_t id, uint8_t address, uint8_t reg, uint8_t bytes, uint8_t *buf);

/** Write a number of \c bytes from a target given by \c address in blocking mode.
 *
 * \param[in] id I2C host peripheral ID.
 * \param[in] address Address of the target to read data from.
 * \param[in] bytes Number of bytes to read from the target.
 * \param[out] buf The buffer into which data from the target are to be stored.
 * 
 * \retval #HAL_SUCCESS Transmission was successful.
 * \retval #HAL_ERROR_REJECTED Transmission failed due to a previous `hal_i2c_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Transmission failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Transmission failed due to a peripheral error.
 */
hal_result_t hal_i2c_host_write_blocking(hal_i2c_peripheral_id_t id, uint8_t address, uint8_t bytes, uint8_t *buf);

/** Read a number of \c bytes from a target's \c reg given by \c address in non-blocking mode.
 *
 * \param[in] id I2C host peripheral ID.
 * \param[in] address Address of the target to read data from.
 * \param[in] reg Register address on the target to read data from.
 * \param[in] bytes Number of bytes to read from the target.
 * \param[out] buf The buffer into which data from the target are to be stored.
 * 
 * \retval #HAL_SUCCESS Reading was successful.
 * \retval #HAL_ERROR_REJECTED Reading failed due to a previous `hal_i2c_init()` call not being made.
 * \retval #HAL_ERROR_PARAM_ERROR Reading failed due to a parameter error.
 * \retval #HAL_ERROR_PERIPHERAL_ERROR Reading failed due to a peripheral error.
 */
hal_result_t hal_i2c_host_read_non_blocking(hal_i2c_peripheral_id_t id, uint8_t address, uint8_t reg, uint8_t bytes, uint8_t *buf);

/** Write a number of \c bytes from a target given by \c address in non-blocking mode.
 *
 * \param[in] id I2C host peripheral ID.
 * \param[in] address Address of the target to read data from.
 * \param[in] bytes Number of bytes to read from the target.
 */
hal_result_t hal_i2c_host_write_non_blocking(hal_i2c_peripheral_id_t id, uint8_t address, uint8_t bytes, uint8_t *buf);

#endif /* HAL_I2C_H */
