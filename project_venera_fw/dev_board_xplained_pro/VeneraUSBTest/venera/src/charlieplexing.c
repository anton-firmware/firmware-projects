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

static hal_gpio_init_t gpio_anode_init =
{
    .pin = gpio_anode
};

static hal_gpio_init_t gpio_cathode_init =
{
    .pin = gpio_cathode
};

static hal_gpio_init_t gpio_input_init =
{
    .pin = gpio_input
};

static void set_inputs_on_pins(uint8_t cathode, uint8_t anode)
{
    for (uint8_t i = 0; i < pin_count_plex; i++)
    {
        if (pin_table[i] == cathode || pin_table[i] == anode)
        {
            continue;
        }

        gpio_input.pin = pin_table[i];
    }

	(void)hal_gpio_pin_init(&gpio_input_init);
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

        for (uint_t i = 0; i < pin_count; i++)
        {
            pin_table[i] = pins[i];
        }
    }

    return result;
}

hal_result_t charlieplexing_set_pin_level(charlieplexed_led_t led_to_set, hal_gpio_level_t pin_level)
{
    gpio_anode.pin = led_to_set.anode;
    gpio_cathode.pin = led_to_set.cathode;

	(void)hal_gpio_pin_init(&gpio_anode_init);
	(void)hal_gpio_pin_init(&gpio_cathode_init);

    set_inputs_on_pins();

    hal_gpio_set_level(&gpio_anode, HAL_GPIO_HIGH);
    hal_gpio_set_level(&gpio_cathode, HAL_GPIO_LOW);
}
