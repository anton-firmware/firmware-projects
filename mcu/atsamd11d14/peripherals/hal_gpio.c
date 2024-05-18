#include <stdbool.h>
#include <stddef.h>

#include "hal_gpio.h"
#include "sam.h"

static volatile uint32_t initialised_pins_bitmap = 0x00000000;

#if defined(__SAMD11C14A__) || defined(__ATSAMD11C14A__)
    static const uint32_t pin_bitmap = 0x00000000;
#elif defined(__SAMD11D14AM__) || defined(__ATSAMD11D14AM__)
    static const uint32_t pin_bitmap = 0xDBC3CFFC;
#elif defined(__SAMD11D14AS__) || defined(__ATSAMD11D14AS__)
    static const uint32_t pin_bitmap = 0xD3C1C3FC;
#elif defined(__SAMD11D14AU__) || defined(__ATSAMD11D14AU__)
    static const uint32_t pin_bitmap = 0x00000000;
#else 
    static const uint32_t pin_bitmap = 0x00000000;
#endif

/** Checks if a given pin is valid on this MCU by checking the pin bitmap.
 * 
 * \param[in] pin The pin to check.
 * 
 * \return \c true if valid, \c false otherwise.
 */
static inline bool is_valid_pin(hal_gpio_pin_t *pin)
{
    return ((pin != NULL) && ((pin_bitmap & (1 << pin->pin)) != 0));
}

/** Checks if a given port is valid.
 * 
 * \param[in] pin The port to check.
 * 
 * \note For the ATSAMD11D14x MCU, there is only one GPIO Port (port A).
 * 
 * \return \c true if the port is valid, false otherwise.
 */
static inline bool is_valid_port(hal_gpio_pin_t *pin)
{
    /* A value of 0 corresponds to port A.*/
    return ((pin != NULL) && (pin->port == 0));
}

/** Checks if a given pin is initialised by accessing the pins bitmap.
 * 
 * \param[in] pin The pin to check.
 * 
 * \return \c true if initialised, \c false otherwise.
 */
static inline bool is_pin_initialised(hal_gpio_pin_t *pin)
{
    return (pin != NULL) && ((initialised_pins_bitmap & (1 << pin->pin)) != 0);
}

/** Sets the alternate function for a GPIO pin.
 * 
 * \param[in] pin The pin to set the alternate function of.
 * \param[in] alt_func The alternate function of the GPIO pin to set.
 */
static inline void set_alternate_function(hal_gpio_pin_t *pin, alt_func_t alt_func)
{
    const uint8_t alt_func_group = pin->pin >> 1;
    
    if (pin->pin & 0x1)
    {
        PORT->Group[0].PMUX[alt_func_group].bit.PMUXO = alt_func;
    }
    else 
    {
        PORT->Group[0].PMUX[alt_func_group].bit.PMUXE = alt_func;
    }
}

hal_result_t hal_gpio_pin_init(hal_gpio_init_t *init_struct)
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    if (!init_struct)
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (is_pin_initialised(&init_struct->pin))
    {
        result = HAL_ERROR_REJECTED;
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
        switch (init_struct->pin.pin_mode)
        {
            case HAL_GPIO_INPUT:
                PORT->Group[0].DIRCLR.reg |= (1u << init_struct->pin.pin);
                PORT->Group[0].PINCFG[init_struct->pin.pin].reg |= PORT_PINCFG_INEN;
                break;
            case HAL_GPIO_OUTPUT_PUSH_PULL:
                PORT->Group[0].DIRSET.reg |= (1u << init_struct->pin.pin);
                break;
            case HAL_GPIO_OUTPUT_OPEN_DRAIN:
                /* TODO: Init open drain. */
                break;
            case HAL_GPIO_ALTERNATE:
                PORT->Group[0].PINCFG[init_struct->pin.pin].bit.PMUXEN = 1;
                set_alternate_function(&init_struct->pin, init_struct->alternate_pin_mapping);
                break;
            default:
                result = HAL_ERROR_PARAM_ERROR;
                break;
        }
        
        if (result != HAL_ERROR_PARAM_ERROR || result != HAL_ERROR_PERIPHERAL_ERROR)
        {
            initialised_pins_bitmap |= (1u << init_struct->pin.pin);
            result = HAL_SUCCESS;
        }
    }

    return result;
}

hal_result_t hal_gpio_clock_init(void)
{
    PM->APBBMASK.reg |= PM_APBBMASK_PORT;
    return HAL_SUCCESS;
}

hal_result_t hal_gpio_clock_teardown(void)
{
    PM->APBBMASK.reg &= ~PM_APBBMASK_PORT;
    return HAL_SUCCESS;
}

hal_result_t hal_gpio_pin_teardown(hal_gpio_pin_t *pin)
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    if (!is_valid_pin(pin))
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (!is_valid_port(pin))
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (!is_pin_initialised(pin))
    {
        result = HAL_ERROR_REJECTED;
    }
    else
    {
        switch (pin->pin_mode)
        {
            case HAL_GPIO_INPUT:
                PORT->Group[0].DIRCLR.reg |= (1u << pin->pin);
                PORT->Group[0].PINCFG[pin->pin].reg &= ~PORT_PINCFG_INEN;
                break;
            case HAL_GPIO_OUTPUT_PUSH_PULL:
                PORT->Group[0].DIRCLR.reg |= (1u << pin->pin);
                break;
            case HAL_GPIO_OUTPUT_OPEN_DRAIN:
                /* TODO: Clear output drain. */
                break;
            case HAL_GPIO_ALTERNATE:
                PORT->Group[0].PINCFG[pin->pin].bit.PMUXEN = 0;
                set_alternate_function(pin, 0);
                break;
            default:
                result = HAL_ERROR_PARAM_ERROR;
                break;
        }

        initialised_pins_bitmap &= ~(1u << pin->pin);
    }

    return result;
}

hal_result_t hal_gpio_set_level(hal_gpio_pin_t *pin, hal_gpio_level_t level)
{
    hal_result_t result = HAL_ERROR_PERIPHERAL_ERROR;

    if (!pin)
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (!is_pin_initialised(pin))
    {
        result = HAL_ERROR_REJECTED;
    }
    else if (!is_valid_port(pin))
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (!is_valid_pin(pin))
    {
        result = HAL_ERROR_PARAM_ERROR;
    }
    else 
    {
        if (level == HAL_GPIO_HIGH)
        {
            PORT->Group[0].OUTSET.reg |= (1u << pin->pin);
        }
        else 
        {
            PORT->Group[0].OUTCLR.reg |= (1u << pin->pin);
            
        }
        
        result = HAL_SUCCESS;
    }

    return result;
}

hal_gpio_level_t hal_gpio_read_level(hal_gpio_pin_t *pin)
{
    hal_gpio_level_t result = HAL_GPIO_INVALID;

    if (!pin)
    {
        /* Do nothing, the pin pointer is invalid. */
    }
    else if (!is_pin_initialised(pin))
    {
        /* Do nothing, the given pin is not initialised. */
    }
    else if (!is_valid_port(pin))
    {
        /* Do nothing, the port is invalid. */
    }
    else if (!is_valid_pin(pin))
    {
        /* Do nothing, the pin is invalid. */
    }
    else
    {
        result = (PORT->Group[0].IN.reg & (1u << pin->pin)) ? HAL_GPIO_HIGH : HAL_GPIO_LOW;
    }

    return result;
}
