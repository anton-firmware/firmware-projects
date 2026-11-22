#include <stdbool.h>

#include "hal_gpio.h"
#include "display_control.h"
#include "display_editor.h"
#include "main.h"

#define MAX_FRAME_COUNT   2u

typedef enum button_phase
{
    UNPRESSED,
    PROCESSING_SHORT,
    PROCESSING_LONG,
    PRESSED
} button_phase_t;

static display_led_state_t frames[MAX_FRAME_COUNT][LED_NUMBER] = {0};
static uint8_t currently_selected_led = 0;
static uint8_t current_frame_number = 0;

static button_phase_t step_button = UNPRESSED;
static button_phase_t toggle_button = UNPRESSED;
static button_phase_t page_button = UNPRESSED;
static button_phase_t mode_button = UNPRESSED;

static bool first_entry = true;

static hal_gpio_level_t read_gpio_debounced(hal_gpio_pin_t pin)
{
    if (hal_gpio_read_level(&pin) == HAL_GPIO_LOW)
    {
        hal_timer_delay(10);

        if (hal_gpio_read_level(&pin) == HAL_GPIO_LOW)
        {
            return HAL_GPIO_LOW;
        }
    }

    return HAL_GPIO_HIGH;
}

static void display_editor_set_led_frame_state(uint8_t frame, uint8_t led_index, display_led_state_t state)
{
    if (frame < MAX_FRAME_COUNT && led_index < LED_NUMBER)
    {
        frames[frame][led_index] = state;
    }
}

void display_editor_edit_mode(void)
{
    if (first_entry)
    {
        display_control_flash_single_led(currently_selected_led);
        first_entry = false;
    }

    switch (step_button)
    {
        case UNPRESSED:
            if (read_gpio_debounced(gpio_button_switch_step) == HAL_GPIO_LOW)
            {
                step_button = PROCESSING_SHORT;
            }
            break;
        case PROCESSING_SHORT:
            display_control_update_display(currently_selected_led, frames[current_frame_number][currently_selected_led]);
            currently_selected_led = (currently_selected_led + 1) % LED_NUMBER;
            display_control_update_display(currently_selected_led, FLASHING);
            step_button = PRESSED;
            break;
        case PRESSED:
            if (read_gpio_debounced(gpio_button_switch_step) == HAL_GPIO_LOW)
            {
                step_button = PRESSED;
            }
            else
            {
                step_button = UNPRESSED;
            }
            break;
    }

    switch (toggle_button)
    {
        case UNPRESSED:
            if (read_gpio_debounced(gpio_button_switch_toggle) == HAL_GPIO_LOW)
            {
                toggle_button = PROCESSING_SHORT;
            }
            break;
        case PROCESSING_SHORT:
            if (display_control_get_current_led_state(currently_selected_led) == FLASHING)
            {
                display_control_update_display(currently_selected_led, ON);
                frames[current_frame_number][currently_selected_led] = ON;
            }
            else
            {
                display_control_update_display(currently_selected_led, FLASHING);
                frames[current_frame_number][currently_selected_led] = OFF;
            }

            toggle_button = PRESSED;
            break;
        case PRESSED:
            if (read_gpio_debounced(gpio_button_switch_toggle) == HAL_GPIO_LOW)
            {
                toggle_button = PRESSED;
            }
            else
            {
                toggle_button = UNPRESSED;
            }
            break;
    }

    switch (page_button)
    {
        case UNPRESSED:
            if (read_gpio_debounced(gpio_button_switch_page) == HAL_GPIO_LOW)
            {
                page_button = PROCESSING_SHORT;
            }
            break;
        case PROCESSING_SHORT:
            current_frame_number = (current_frame_number + 1) % MAX_FRAME_COUNT;
            first_entry = true;
            for (uint8_t i = 0; i < LED_NUMBER; i++)
            {
                display_control_update_display(i, frames[current_frame_number][i]);
            }
            currently_selected_led = 0;
            page_button = PRESSED;
            break;
        case PRESSED:
            if (read_gpio_debounced(gpio_button_switch_page) == HAL_GPIO_LOW)
            {
                page_button = PRESSED;
            }
            else
            {
                page_button = UNPRESSED;
            }
            break;
    }
}
