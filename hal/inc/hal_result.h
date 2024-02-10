#ifndef HAL_RESULT_H
#define HAL_RESULT_H

/** \file
 * 
 * File containing result types that are returned from the HAL. 
 */

#include <stdint.h>

/** Type representing result. 
 * 
 * This type is used to represent various results of HAL API calls.
 * 
 * Successful results are typically represented using values below 127 (n <= 127). 
 * Unsuccessful results are represented using values above 127 (n > 127).
 */
typedef uint8_t hal_result_t;

/** 
 * \name Success codes.
 * 
 * \{
 * \details 
 */

/** Value representing the requested operation was successful. */
#define HAL_SUCCESS ((hal_result_t)0)

/** \} End of Success codes. */

/** 
 * \name Failure codes.
 * 
 * \{
 * \details 
 */

/** Value representing a general failure not covered by the other cases. */
#define HAL_ERROR_GENERIC ((hal_result_t)128)

/** Value representing the requested operation was rejected. */
#define HAL_ERROR_REJECTED ((hal_result_t)129)

/** Value representing a parameter error. */
#define HAL_ERROR_PARAM_ERROR ((hal_result_t)130)

/** Value representing an error with a device. */
#define HAL_ERROR_DEVICE_ERROR ((hal_result_t)131)

/** Value representing an error with a peripheral. */
#define HAL_ERROR_PERIPHERAL_ERROR ((hal_result_t)132)

/** Value representing an error with communications. */
#define HAL_ERROR_COMMS_ERROR ((hal_result_t)133)

/** Value representing an error a read operation. */
#define HAL_ERROR_READ_ERROR ((hal_result_t)134)

/** Value representing an error with a write operation. */
#define HAL_ERROR_WRITE_ERROR ((hal_result_t)135)

/** Value representing an unsupported operation. */
#define HAL_ERROR_UNSUPPORTED ((hal_result_t)136)

/** \} End of Failure codes. */

#endif /* HAL_RESULT_H */