#include <stdbool.h>

#include "hal_gpio.h"
#include "sam.h"

static volatile bool peripheral_initialised = false;

#if   defined(__SAMD11C14A__) || defined(__ATSAMD11C14A__)
    static const uint32_t pin_bitmap = 0x00000000;
#elif defined(__SAMD11D14AM__) || defined(__ATSAMD11D14AM__)
    static const uint32_t pin_bitmap = 0x00000000;
#elif defined(__SAMD11D14AS__) || defined(__ATSAMD11D14AS__)
    static const uint32_t pin_bitmap = 0x00000000;
#elif defined(__SAMD11D14AU__) || defined(__ATSAMD11D14AU__)
    static const uint32_t pin_bitmap = 0x00000000;
#else 
    static const uint32_t pin_bitmap = 0x00000000;
#endif

static inline bool is_valid_pin(hal_gpio_pin_t *pin)
{
    return (pin_bitmap & (1 << pin->pin)) != 0;
}

/** Checks if a given port is valid.
 * 
 * \param[in] pin The port to check.
 * 
 * \note For the ATSAMD11D14x MCU, there is only one GPIO Port.
 * 
 * \return \c true if the port is valid, false otherwise.
 */
static inline bool is_valid_port(hal_gpio_pin_t *pin)
{
    /* A value of 0 corresponds to port A.*/
    return pin->port == 0;
}

hal_result_t hal_gpio_init(hal_gpio_init_t *init_struct)
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    if (peripheral_initialised)
    {
        result = HAL_ERROR_REJECTED;
    }
    else if (!init_struct)
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (!is_valid_port(&init_struct->pin))
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (!is_valid_pin(&init_struct->pin))
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else
    {

        

        peripheral_initialised = true;

        result = HAL_SUCCESS;
    }

    return result;
}

hal_result_t hal_gpio_clock_init(void)
{
    /* Not needed on ATSAMD11D14x. */
    return HAL_SUCCESS;
}

hal_result_t hal_gpio_clock_teardown(void)
{
    /* Not needed on ATSAMD11D14x. */
    return HAL_SUCCESS;
}

hal_result_t hal_gpio_teardown(void)
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    if (!peripheral_initialised)
    {
        result = HAL_ERROR_REJECTED;
    }
}

hal_result_t hal_gpio_set_level(hal_gpio_pin_t *pin, hal_gpio_level_t level)
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;
}

hal_gpio_level_t hal_gpio_read_level(hal_gpio_pin_t *pin)
{
    hal_gpio_level_t result = HAL_GPIO_INVALID;

    if (!pin)
    {
        // Do nothing, the pin pointer is invalid.
    }
    else if (!is_valid_port(pin))
    {
        // Do nothing, the port is invalid.
    }
    else if (!is_valid_pin(pin))
    {
        // Do nothing, the pin is invalid.
    }
    else
    {
        result = (PORT->Group[0].IN.reg & pin->pin) ? HAL_GPIO_HIGH : HAL_GPIO_LOW;
    }

    return result;
}
