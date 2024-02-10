#ifndef HAL_GPIO
#define HAL_GPIO

#include "../hal_result.h"

typedef enum hal_gpio_mode
{
    HAL_GPIO_INPUT,             /*!< Internal clock. (e.g. PLL, HSI) */
    HAL_GPIO_OUTPUT_PUSH_PULL,  /*!< Internal clock. (e.g. PLL, HSI) */
    HAL_GPIO_OUTPUT_OPEN_DRAIN, /*!< Internal clock. (e.g. PLL, HSI) */

} hal_gpio_pin_mode_t;

typedef enum hal_gpio_speed
{
    HAL_GPIO_VERY_SLOW,
    HAL_GPIO_SLOW,
    HAL_GPIO_NORMAL,
    HAL_GPIO_FAST,
    HAL_GPIO_VERY_FAST,

} hal_gpio_pin_speed_t;

/** Structure representing a pin on a port on an MCU. */
typedef struct hal_gpio_pin
{
    uint8_t pin;  /*!< Internal clock. (e.g. PLL, HSI) */
    uint8_t port; /*!< Internal clock. (e.g. PLL, HSI) */

} hal_gpio_pin_t;

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

#endif
