#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "hal_gpio.h"
#include "hal_timer.h"
#include "sam.h"

/* For this MCU, PORTA is the only group and it's always 0. */
#define PORTA_GROUP                           0u
#define EXTERNAL_INTERRUPT_LINES              7u
#define PINS_ON_MCU                           32u
#define EXTERNAL_INTERRUPT_ALTERNATE_FUNCTION 0x00u
#define BUTTON_DEBOUNCING_THRESHOLD           22u

static hal_gpio_trigger_event_t external_interrupt_pins[EXTERNAL_INTERRUPT_LINES];

static volatile uint32_t last_interrupt_time;
static volatile uint32_t current_interrupt_time;

/* Array mapping pin number to external interrupt lines. Some pins map to the same interrupt line. 
   See Table 6-1. PORT Function Multiplexing. */
static uint8_t pin_external_line_map[PINS_ON_MCU] = 
{
	0xFFu, /* PA00 - NONE.   */ 
	0xFFu, /* PA01 - NONE.   */
	2u, /* PA02 - EXTINT[2]. */
	3u, /* PA03 - EXTINT[3]. */
	4u, /* PA04 - EXTINT[4]. */
	5u, /* PA05 - EXTINT[5]. */
	6u, /* PA06 - EXTINT[6]. */
	7u, /* PA07 - EXTINT[7]. */
	6u, /* PA08 - EXTINT[6]. */
	7u, /* PA09 - EXTINT[7]. */
	2u, /* PA10 - EXTINT[2]. */
	3u, /* PA11 - EXTINT[3]. */
	0xFFu, /* PA12 - NONE.   */
	0xFFu, /* PA13 - NONE.   */
	0xFFu, /* PA14 - NMI (Not EXTINT). */
	1u, /* PA15 - EXTINT[1]. */
	0u, /* PA16 - EXTINT[0]. */
	1u, /* PA17 - EXTINT[1]. */
	0xFFu, /* PA18 - NONE.   */
	0xFFu, /* PA19 - NONE.   */
	0xFFu, /* PA20 - NONE.   */
	0xFFu, /* PA21 - NONE.   */
	6u, /* PA22 - EXTINT[6]. */
	7u, /* PA23 - EXTINT[7]. */
	4u, /* PA24 - EXTINT[4]. */
	5u, /* PA25 - EXTINT[5]. */
	0xFFu, /* PA26 - NONE.   */
	7u, /* PA27 - EXTINT[7]. */
	0xFFu, /* PA28 - NONE    */
	0xFFu, /* PA29 - NONE.   */
	2u, /* PA30 - EXTINT[2]. */
	3u, /* PA31 - EXTINT[3]. */
};


static uint32_t initialised_pins_bitmap = 0x00000000u;

/** Valid pins for a particular MCU depending on the compiler flag.
 * 
 */
#if defined(__SAMD11C14A__) || defined(__ATSAMD11C14A__)
    static const uint32_t pin_bitmap = 0x00000000u;
#elif defined(__SAMD11D14AM__) || defined(__ATSAMD11D14AM__)
    static const uint32_t pin_bitmap = 0xDBC3CFFCu;
#elif defined(__SAMD11D14AS__) || defined(__ATSAMD11D14AS__)
    static const uint32_t pin_bitmap = 0xD3C1C3FCu;
#elif defined(__SAMD11D14AU__) || defined(__ATSAMD11D14AU__)
    static const uint32_t pin_bitmap = 0x00000000u;
#else 
    static const uint32_t pin_bitmap = 0x00000000u;
#endif

/** Checks if a given pin is valid on this MCU by checking the pin bitmap.
 * 
 * \param[in] pin The pin to check.
 * 
 * \return \c true if valid, \c false otherwise.
 */
static inline bool is_valid_pin(hal_gpio_pin_t *pin)
{
    return ((pin != NULL) && ((pin_bitmap & (1 << pin->pin)) != 0u));
}

/** Checks if a given port is valid.
 * 
 * \param[in] pin The port to check.
 * 
 * \note For the ATSAMD11D14x MCU, there is only one GPIO Port (port A).
 * 
 * \return \c true if the port is valid, \c false otherwise.
 */
static inline bool is_valid_port(hal_gpio_pin_t *pin)
{
    return ((pin != NULL) && (pin->port == PORTA_GROUP));
}

/** Checks if a given pin is initialised by accessing the pins bitmap.
 * 
 * \param[in] pin The pin to check.
 * 
 * \return \c true if initialised, \c false otherwise.
 */
static inline bool is_pin_initialised(hal_gpio_pin_t *pin)
{
    return (pin != NULL) && ((initialised_pins_bitmap & (1 << pin->pin)) != 0u);
}

/** Sets the alternate function for a GPIO pin.
 * 
 * \param[in] pin The pin to set the alternate function of.
 * \param[in] alt_func The alternate function of the GPIO pin to set.
 */
static inline void set_alternate_function(hal_gpio_pin_t *pin, alt_func_t alt_func)
{
    const uint8_t alt_func_group = pin->pin >> 1u;
	
    PORT->Group[PORTA_GROUP].PINCFG[pin->pin].bit.PMUXEN = 1u;
    
    /* Determine if a pin is in an odd or even group by looking at the last bit. */
    if (pin->pin & 0x1u)
    {
        PORT->Group[PORTA_GROUP].PMUX[alt_func_group].bit.PMUXO = alt_func;
    }
    else 
    {
        PORT->Group[PORTA_GROUP].PMUX[alt_func_group].bit.PMUXE = alt_func;
    }
}

/** Sets the pull up/pull down function for a GPIO pin.
 * 
 * \param[in] pin The pin to set the pull up/pull down function of.
 */
static inline void set_pull_up_pull_down(hal_gpio_pin_t *pin)
{
    if (pin->pull_up_mode)
    {
        if (pin->pull_up_mode == HAL_GPIO_PULL_UP)
        {
            PORT->Group[PORTA_GROUP].PINCFG[pin->pin].bit.PULLEN = 1u;
			PORT->Group[PORTA_GROUP].OUTSET.reg |= (1u << pin->pin);
        }
        else
        {
            PORT->Group[PORTA_GROUP].PINCFG[pin->pin].bit.PULLEN = 0u;
        }
    }
}

/** Helper function to set up the clock source for the EIC peripheral.
 * 
 * In order to set a generic clock, we do a 16 bit write of the configurations 
 * and the ID, see page 99 of ATSAMD11 reference manual.
 */
static inline void setup_eic_gclk(void)
{
    uint16_t clk_ctl_reg_value = 0;

    /* Set the EIC core clock to be Generic Clock Generator 0 (Internal 8MHz oscilator). 
     * Note: On reset, the OSC8M is fed through a divide by 8 step, so this clock is actually 1MHz. 
     */
    clk_ctl_reg_value |= (GCLK_CLKCTRL_ID_EIC | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0);

    GCLK->CLKCTRL.reg = clk_ctl_reg_value; 

    /* Wait for syncronisation. */
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
}

/** Enables the external interrupt controller (EIC). */
static inline void enable_external_interrupt_controller(void)
{
	EIC->CTRL.bit.ENABLE = 1u;
    /* Wait for syncronisation. */
	while (EIC->STATUS.reg & EIC_STATUS_SYNCBUSY);
}

/** Disables the external interrupt controller (EIC). */
static inline void teardown_external_interrupt_controller(void)
{
    NVIC_DisableIRQ(EIC_IRQn);
	EIC->CTRL.reg |= EIC_CTRL_SWRST;
    /* Wait for syncronisation. */
    while (EIC->STATUS.reg & EIC_STATUS_SYNCBUSY);
}

/** Sets up the external interrupt line for a pin to the given trigger.
 * 
 * \param[in] pin The pin to set the pull up/pull down function of.
 * \param[in] callback The callback function to be used when the button is pressed.
 */
static inline void set_input_trigger_type(hal_gpio_pin_t *pin, hal_gpio_trigger_event_t callback)
{
	if (pin->trigger && callback)
	{
		const uint8_t external_interrupt_line = pin_external_line_map[pin->pin];
		/* Set bit 4 to 1, filter enable, see 20.8.10 Configuration - ATSAMD11 reference manual. */
		uint8_t config_nibble = 0x08u;
		
		set_alternate_function(pin, EXTERNAL_INTERRUPT_ALTERNATE_FUNCTION);
	
		if (pin->trigger == HAL_GPIO_RISING)
		{
			config_nibble |= 0x1u;
		}
		else
		{
			config_nibble |= 0x2u;
		}
		
		EIC->CONFIG[0].reg |= (config_nibble << (external_interrupt_line << 2u));
		EIC->INTENSET.reg |= (0x1u << external_interrupt_line);
		NVIC_EnableIRQ(EIC_IRQn);
		external_interrupt_pins[external_interrupt_line] = callback;
	}
}

/** ISR for the external interrupt controller. 
 * 
 * \note KNOWN LIMITATION: In this mplementation if two or more buttons are pressed
 *       simultaneously within the same debounce window, the second press will be discarded.
 *       To be fixed at a later date.
 */
void EIC_Handler(void)
{
	current_interrupt_time = hal_timer_get_tick();
	
	if (current_interrupt_time - last_interrupt_time > BUTTON_DEBOUNCING_THRESHOLD)
	{
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT0)
		{
			external_interrupt_pins[0]();
			EIC->INTFLAG.bit.EXTINT0 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT1)
		{
			external_interrupt_pins[1]();
			EIC->INTFLAG.bit.EXTINT1 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT2)
		{
			external_interrupt_pins[2]();
			EIC->INTFLAG.bit.EXTINT2 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT3)
		{
			external_interrupt_pins[3]();
			EIC->INTFLAG.bit.EXTINT3 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT4)
		{
			external_interrupt_pins[4]();
			EIC->INTFLAG.bit.EXTINT4 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT5)
		{
			external_interrupt_pins[5]();
			EIC->INTFLAG.bit.EXTINT5 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT6)
		{
			external_interrupt_pins[6]();
			EIC->INTFLAG.bit.EXTINT6 = 1u;
		}
		
		if (EIC->INTFLAG.reg & EIC_INTFLAG_EXTINT7)
		{
			external_interrupt_pins[7]();
			EIC->INTFLAG.bit.EXTINT7 = 1u;
		}
		
		last_interrupt_time = current_interrupt_time;
	}
	else
	{
		EIC->INTFLAG.reg = 0xFF;
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
                PORT->Group[PORTA_GROUP].DIRCLR.reg = (1u << init_struct->pin.pin);
                PORT->Group[PORTA_GROUP].PINCFG[init_struct->pin.pin].reg |= PORT_PINCFG_INEN;
                set_pull_up_pull_down(&init_struct->pin);
                set_input_trigger_type(&init_struct->pin, init_struct->trigger_event_cb);
                enable_external_interrupt_controller();
                break;
            case HAL_GPIO_OUTPUT_PUSH_PULL:
                PORT->Group[PORTA_GROUP].DIRSET.reg = (1u << init_struct->pin.pin);
                break;
            case HAL_GPIO_OUTPUT_OPEN_DRAIN:
                /* TODO: Init open drain. */
                break;
            case HAL_GPIO_ALTERNATE:
                set_alternate_function(&init_struct->pin, init_struct->alternate_pin_mapping);
                break;
            default:
                result = HAL_ERROR_PARAM_ERROR;
                break;
        }
        
        if ((result != HAL_ERROR_PARAM_ERROR) && (result != HAL_ERROR_PERIPHERAL_ERROR))
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
    PM->APBAMASK.reg |= PM_APBAMASK_EIC;
	/* We're using filtering, so enable GCLK, see 20.6.2.1 Initialization ATSAMD11 reference manual. */
	setup_eic_gclk();
    return HAL_SUCCESS;
}

hal_result_t hal_gpio_clock_teardown(void)
{
    PM->APBBMASK.reg &= ~PM_APBBMASK_PORT;
	PM->APBAMASK.reg &= ~PM_APBAMASK_EIC;
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
                PORT->Group[PORTA_GROUP].DIRCLR.reg = (1u << pin->pin);
                PORT->Group[PORTA_GROUP].PINCFG[pin->pin].reg &= ~PORT_PINCFG_INEN;
                PORT->Group[PORTA_GROUP].PINCFG[pin->pin].bit.PULLEN = 0u;
                break;
            case HAL_GPIO_OUTPUT_PUSH_PULL:
                PORT->Group[PORTA_GROUP].DIRCLR.reg = (1u << pin->pin);
                break;
            case HAL_GPIO_OUTPUT_OPEN_DRAIN:
                /* TODO: Clear output drain. */
                break;
            case HAL_GPIO_ALTERNATE:
                PORT->Group[PORTA_GROUP].PINCFG[pin->pin].bit.PMUXEN = 0;
                set_alternate_function(pin, 0u);
                break;
            default:
                result = HAL_ERROR_PARAM_ERROR;
                break;
        }

        initialised_pins_bitmap &= ~(1u << pin->pin);
		teardown_external_interrupt_controller();
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
            PORT->Group[PORTA_GROUP].OUTSET.reg = (1u << pin->pin);
        }
        else 
        {
            PORT->Group[PORTA_GROUP].OUTCLR.reg = (1u << pin->pin);
            
        }
        
        result = HAL_SUCCESS;
    }

    return result;
}

hal_result_t hal_gpio_toggle_level(hal_gpio_pin_t *pin)
{
    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    if (!pin)
    {
        /* Do nothing, the pin pointer is invalid. */
    }
    else if (!is_pin_initialised(pin))
    {
        result = HAL_ERROR_REJECTED;
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
        PORT->Group[PORTA_GROUP].OUTTGL.reg = (1u << pin->pin);

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
        result = (PORT->Group[PORTA_GROUP].IN.reg & (1u << pin->pin)) ? HAL_GPIO_HIGH : HAL_GPIO_LOW;
    }

    return result;
}
