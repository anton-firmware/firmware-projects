#include <stddef.h>
#include <stdint.h>

#include "hal_gpio.h"
#include "hal_result.h"
#include "charlieplexing.h"

#define MAX_PIN_COUNT 32u
#define PORT_A_INDEX 0u

static pin_table[MAX_PIN_COUNT];

static uint8_t pin_count_plex;

static hal_gpio_pin_t gpio_anode =
{
	.pin = 0,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

static hal_gpio_pin_t gpio_cathode =
{
	.pin = 0,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

static hal_gpio_pin_t gpio_input =
{
	.pin = 0,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
};

static charlieplexed_led_t last_configured_pin;

static void set_inputs_on_pins(uint8_t cathode, uint8_t anode)
{
	for (uint8_t i = 0; i < pin_count_plex; i++)
	{
		if (pin_table[i] == cathode || pin_table[i] == anode)
		{
			continue;
		}

		gpio_input.pin = pin_table[i];
		
		hal_gpio_init_t gpio_input_init =
		{
			.pin = gpio_input
			.pull_up_mode = HAL_GPIO_PULL_DOWN
		};

		(void)hal_gpio_pin_init(&gpio_input_init);
	}
}

hal_result_t charlieplexing_initialise_pin_table(uint8_t *pins, uint8_t pin_count)
{
	hal_result_t result = HAL_SUCCESS;

	if (pins == NULL || pin_count == 0 || pin_count > MAX_PIN_COUNT)
	{
		result = HAL_ERROR_PARAM_ERROR;
	}
	else
	{
		pin_count_plex = pin_count;

		for (uint8_t i = 0; i < pin_count; i++)
		{
			pin_table[i] = pins[i];
		}
	}

	return result;
}

hal_result_t charlieplexing_set_pin_level(charlieplexed_led_t led_to_set, hal_gpio_level_t pin_level)
{
	hal_gpio_pin_teardown(&gpio_anode);
	hal_gpio_pin_teardown(&gpio_cathode);
	
	gpio_anode.pin = led_to_set.anode;
	gpio_cathode.pin = led_to_set.cathode;

	hal_gpio_init_t gpio_anode_init =
	{
		.pin = gpio_anode
	};

	hal_gpio_init_t gpio_cathode_init =
	{
		.pin = gpio_cathode
	};

	last_configured_pin = led_to_set;

	(void)hal_gpio_pin_init(&gpio_anode_init);
	(void)hal_gpio_pin_init(&gpio_cathode_init);

	set_inputs_on_pins(led_to_set.cathode, led_to_set.anode);

	hal_gpio_set_level(&gpio_anode, HAL_GPIO_HIGH);
	hal_gpio_set_level(&gpio_cathode, HAL_GPIO_LOW);
}
