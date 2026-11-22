#include <stdbool.h>
#include <string.h>

#include "hal_gpio.h"
#include "hal_timer.h"
#include "hal_flash.h"
#include "display_control.h"
#include "display_editor.h"
#include "main.h"

static display_frames_t display_frames;
static volatile display_frames_t* flash_frames;
static uint8_t currently_selected_led = 0;
static uint8_t current_frame_number = 0;

static button_phase_t step_button = UNPRESSED;
static button_phase_t toggle_button = UNPRESSED;
static button_phase_t page_button = UNPRESSED;
static button_phase_t mode_button = UNPRESSED;

static uint32_t mode_press_tick = 0;

static bool first_entry = true;

static void display_editor_set_led_frame_state(uint8_t frame, uint8_t led_index, display_led_state_t state)
{
    if (frame < MAX_FRAME_COUNT && led_index < LED_NUMBER)
    {
        display_frames.frames[frame][led_index] = state;
    }
}

uint32_t display_editor_get_frame_magic(void)
{
    return display_frames.magic;
}

const display_led_state_t* display_editor_get_frame_array(uint8_t frame_index)
{
    if (frame_index < MAX_FRAME_COUNT)
    {
        return display_frames.frames[frame_index];
    }
}

void display_editor_load_from_flash(void)
{
    flash_frames = &config_row_start;
    
    if (flash_frames->magic == DISPLAY_MAGIC)
    {
        display_frames = *flash_frames;
    }
}

void display_editor_edit_mode(void)
{   
    if (first_entry)
    {    
        for (uint8_t i = 0; i < LED_NUMBER; i++)
        {
            display_control_update_display(i, display_frames.frames[current_frame_number][i]);
        }
        display_control_update_display(0, FLASHING);
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
            display_control_update_display(currently_selected_led, display_frames.frames[current_frame_number][currently_selected_led]);
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
                display_frames.frames[current_frame_number][currently_selected_led] = ON;
            }
            else
            {
                display_control_update_display(currently_selected_led, FLASHING);
                display_frames.frames[current_frame_number][currently_selected_led] = OFF;
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
                display_control_update_display(i, display_frames.frames[current_frame_number][i]);
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

    switch (mode_button)
    {
        case UNPRESSED:
            if (read_gpio_debounced(gpio_button_switch_mode) == HAL_GPIO_LOW)
            {
                mode_press_tick = hal_timer_get_tick();
                mode_button = PROCESSING_LONG;
            }
            break;
            
        case PROCESSING_LONG:
            if ((read_gpio_debounced(gpio_button_switch_mode) == HAL_GPIO_LOW) && (hal_timer_get_tick() - mode_press_tick > 100000))
            {
                display_frames.magic = DISPLAY_MAGIC;
                (void)hal_flash_write_data((uint32_t *)&display_frames, sizeof(display_frames), &config_row_start);
                lunokhod_switch_mode();
                first_entry = true;
                mode_button = PRESSED;
            }
            else if ((read_gpio_debounced(gpio_button_switch_mode) == HAL_GPIO_HIGH))
            {
                mode_button = UNPRESSED;
            }
            break;

        case PRESSED:
            if (read_gpio_debounced(gpio_button_switch_mode) == HAL_GPIO_LOW)
            {
                mode_button = PRESSED;
            }
            else
            {
                mode_button = UNPRESSED;
            }
            break;
    }
}
