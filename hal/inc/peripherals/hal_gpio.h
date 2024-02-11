#ifndef HAL_GPIO_H
#define HAL_GPIO_H

/** \file
 * 
 * File containing definitions for GPIO functions.
 */

#include "../hal_result.h"

typedef enum hal_gpio_level
{
    HAL_GPIO_LOW,  /*!< GPIO Level low. */
    HAL_GPIO_HIGH, /*!< GPIO Level high. */

} hal_gpio_level_t;

/** Definitions related to GPIO input modes. */
typedef enum hal_gpio_mode
{
    HAL_GPIO_INPUT,             /*!< GPIO Input. */
    HAL_GPIO_OUTPUT_PUSH_PULL,  /*!< GPIO Output set up in a push-pull configuration. */
    HAL_GPIO_OUTPUT_OPEN_DRAIN, /*!< GPIO Output set up in an open drain configuration. */

} hal_gpio_pin_mode_t;

/** Definitions related to GPIO triggers. */
typedef enum hal_gpio_triggers
{
    HAL_GPIO_RISING,  /*!< GPIO trigger on a rising edge. */
    HAL_GPIO_FALLING, /*!< GPIO trigger on a falling edge. */

} hal_gpio_pin_trigger_t;

/** Definitions related to GPIO speeds. */
typedef enum hal_gpio_speed
{
    HAL_GPIO_VERY_SLOW, /*!< GPIO very slow mode. */
    HAL_GPIO_SLOW,      /*!< GPIO slow mode. */
    HAL_GPIO_NORMAL,    /*!< GPIO normal mode. */
    HAL_GPIO_FAST,      /*!< GPIO fast mode. */
    HAL_GPIO_VERY_FAST, /*!< GPIO very fast mode. */

} hal_gpio_pin_speed_t;

/** Structure representing a pin on a port on an MCU. */
typedef struct hal_gpio_pin
{
    uint8_t pin;  /*!< GPIO Pin. */
    uint8_t port; /*!< GPIO Port. */

} hal_gpio_pin_t;

/** Structure representing GPIO initialisation. */
typedef struct hal_gpio_init
{
    hal_gpio_pin_mode_t  pin_mode;
    hal_gpio_pin_t       pin;
    hal_gpio_pin_speed_t speed;

} hal_gpio_init_t;

/** Initialise GPIO.
 *
 *  \param[in] init_struct GPIO initialisation structure.
 * 
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_gpio_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_gpio_init(hal_gpio_init_t init_struct);

/** Initialise GPIO clocks.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_gpio_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_gpio_clock_init(void);

/** Teardown previously intialised GPIO clocks.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due a previous `hal_gpio_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_gpio_clock_teardown(void);

/** Teardown resources set up by `hal_gpio_init()`.
 * 
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_gpio_init()` call not being made.
 */
hal_result_t hal_gpio_teardown(void);

/** Set the state of a GPIO pin.
 * 
 *  \param[in] pin GPIO pin.
 *  \param[in] level Pin level.
 * 
 *  \retval #HAL_SUCCESS Pin state successfully set.
 *  \retval #HAL_ERROR_REJECTED Pin state unable to be set due to a previous `hal_gpio_init()` call not being made.
 */
hal_result_t hal_gpio_set_level(hal_gpio_pin_t pin, hal_gpio_level_t level);

/** Read the state of a GPIO pin.
 * 
 *  \param[in] pin GPIO pin.
 * 
 *  \retval #HAL_GPIO_LOW GPIO low level.
 *  \retval #HAL_GPIO_High GPIO high level.
 */
hal_gpio_level_t hal_gpio_read_level(hal_gpio_pin_t pin);

#endif /* HAL_GPIO_H */
