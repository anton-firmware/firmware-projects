#ifndef CHARLIEPLEXING_H
#define CHARLIEPLEXING_H

#include <stdint.h>

#include "hal_gpio.h"
#include "hal_result.h"

typedef struct led
{
    uint8_t anode; /*!< Pin of the anode (+ve end) of the LED. */
    uint8_t cathode; /*!< Pin of the cathode (-ve end) of the LED. */
} charlieplexed_led_t;

/** Initialise the charlieplexing driver by providing a list of pins that are in the charlieplex array.
 *
 *  \param[in] pins Pointer to an array of GPIO pins.
 *  \param[in] pin_count The number of pins in the array.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_PARAM_ERROR The \c pins array was \c NULL.
 */
hal_result_t charlieplexing_initialise_pin_table(uint8_t *pins, uint8_t pin_count);

/** Set a correpsonding charlieplexed LED high.
 *
 *  Given the provided \c led_to_set, configures the anode and cathode as an output, and sets to HIGH and LOW respectively,
 *  and the rest of the pins (as provided in the \c charlieplexing_initialise_pin_table function) to inputs.
 * 
 *  \param[in] led_to_set The charlieplexed LED to turn on.
 *  \param[in] pin_level The level to set the LED too.
 *
 *  \retval #HAL_SUCCESS Initialisation was successful.
 *  \retval #HAL_ERROR_PARAM_ERROR The \c pins array is was \c NULL.
 */
hal_result_t charlieplexing_set_pin_level(charlieplexed_led_t led_to_set, hal_gpio_level_t pin_level);

#endif