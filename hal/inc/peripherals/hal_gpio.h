#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

/** \file
 *
 * File containing definitions for GPIO functions.
 */

#include "hal_result.h"

typedef enum hal_gpio_level
{
    HAL_GPIO_LOW,     /*!< GPIO Level low. */
    HAL_GPIO_HIGH,    /*!< GPIO Level high. */
    HAL_GPIO_INVALID, /*!< GPIO Level invalid. */

} hal_gpio_level_t;

/** Definitions related to GPIO input modes. */
typedef enum hal_gpio_mode
{
    HAL_GPIO_INPUT,             /*!< GPIO Input. */
    HAL_GPIO_OUTPUT_PUSH_PULL,  /*!< GPIO Output set up in a push-pull configuration. */
    HAL_GPIO_OUTPUT_OPEN_DRAIN, /*!< GPIO Output set up in an open drain configuration. */
    HAL_GPIO_ALTERNATE,         /*!< GPIO Pin set in an alternate configuration. */

} hal_gpio_pin_mode_t;

/** Definitions related to GPIO pull-up/pull-down configurations. */
typedef enum hal_gpio_pull_up_mode
{
    HAL_GPIO_PULL_UP,    /*!< GPIO Pull-up enabled. */
    HAL_GPIO_PULL_DOWN,  /*!< GPIO Pull-down enabled. */

} hal_gpio_pull_up_mode_t;

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
    uint8_t pin;                          /*!< GPIO Pin. */
    uint8_t port;                         /*!< GPIO Port. */
    hal_gpio_pin_mode_t pin_mode;         /*!< GPIO mode. */
    hal_gpio_pull_up_mode_t pull_up_mode; /*!< GPIO pull up mode. */
    hal_gpio_pin_speed_t speed;           /*!< GPIO pin speed. */
    hal_gpio_pin_trigger_t trigger;       /*!< GPIO trigger. */

} hal_gpio_pin_t;

/** Value representing alternate function for a GPIO pin. The value of which can usually be obtained from the device's datasheet. */
typedef uint16_t alt_func_t;

/** Callback definition for carrying out a user-defined action on a GPIO trigger. */
typedef void (*hal_gpio_trigger_event_t)(void);

/** Structure representing GPIO initialisation. */
typedef struct hal_gpio_init
{
    hal_gpio_pin_t             pin;                      /*!< GPIO pin. */
    alt_func_t                 alternate_pin_mapping;    /*!< GPIO alternate function value. */
    hal_gpio_trigger_event_t   trigger_event_cb;         /*!< GPIO trigger callback. */

} hal_gpio_init_t;

/** Initialise a GPIO pin given by the \c init_struct.
 *
 *  \param[in] init_struct Pointer to a GPIO initialisation structure.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_PARAM_ERROR An invalid parameter was detected.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_gpio_pin_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_gpio_pin_init(hal_gpio_init_t *init_struct);

/** Initialise clocks used by the GPIO peripheral.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_REJECTED Initialisation failed due to a previous `hal_gpio_clock_init()` call being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Initialisation failed due to a peripheral error.
 */
hal_result_t hal_gpio_clock_init(void);

/** Teardown previously intialised GPIO clocks.
 *
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_gpio_clock_init()` call not being made.
 *  \retval #HAL_ERROR_PERIPHERAL_ERROR Teardown failed due to a peripheral error.
 */
hal_result_t hal_gpio_clock_teardown(void);

/** Teardown resources set up by `hal_gpio_pin_init()` for a specific GPIO pin.
 * 
 *  Resets the pin to an input state, clears the alternate function and trigger (if selected), disables pull-up (if enabled).
 * 
 *  \retval #HAL_SUCCESS Teardown was successful.
 *  \retval #HAL_ERROR_REJECTED Teardown failed due to a previous `hal_gpio_pin_init()` call not being made.
 *  \retval #HAL_ERROR_PARAM_ERROR Teardown failed due to a parameter error.
 */
hal_result_t hal_gpio_pin_teardown(hal_gpio_pin_t *pin);

/** Set the state of a GPIO pin.
 *
 *  \param[in] pin Pointer to a GPIO pin.
 *  \param[in] level Pin level.
 *
 *  \retval #HAL_SUCCESS Pin state successfully set.
 *  \retval #HAL_ERROR_PARAM_ERROR An invalid pin, port, or level was specified.
 *  \retval #HAL_ERROR_REJECTED Pin state unable to be set due to a previous `hal_gpio_pin_init()` call not being made.
 */
hal_result_t hal_gpio_set_level(hal_gpio_pin_t *pin, hal_gpio_level_t level);

/** Toggle the state of a GPIO pin.
 *
 *  Toggles between #HAL_GPIO_LOW and #HAL_GPIO_HIGH.  
 * 
 *  \param[in] pin Pointer to a GPIO pin.
 *
 *  \retval #HAL_SUCCESS Pin state successfully toggled.
 *  \retval #HAL_ERROR_PARAM_ERROR An invalid pin, or port, was specified.
 *  \retval #HAL_ERROR_REJECTED Pin state unable to be toggled due to a previous `hal_gpio_pin_init()` call not being made.
 */
hal_result_t hal_gpio_toggle_level(hal_gpio_pin_t *pin);

/** Read the state of a GPIO pin.
 *
 *  \param[in] pin Pointer to a GPIO pin.
 *
 *  \retval #HAL_GPIO_LOW GPIO low level.
 *  \retval #HAL_GPIO_High GPIO high level.
 *  \retval #HAL_GPIO_INVALID Invalid GPIO level due to a peripheral error, parameter error, or a previous `hal_gpio_pin_init()` call not being made.
 */
hal_gpio_level_t hal_gpio_read_level(hal_gpio_pin_t *pin);

#endif /* HAL_GPIO_H */
