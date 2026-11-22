#include "hal_core_unique_id.h"
#include "hal_timer.h"

#include "display_control.h"
#include "display_editor.h"
#include "display_replay.h"
#include "main.h"

#define SERIAL_NUMBER_WORDS 4u

static const display_led_state_t *frame;
static uint32_t unique_id[SERIAL_NUMBER_WORDS];
static display_led_state_t fixed_frame[MAX_FRAME_COUNT][LED_NUMBER];
static uint8_t current_frame_index;
static uint32_t frame_timer;
static uint32_t previous_frame_timer;

static button_phase_t mode_button = UNPRESSED;
static uint32_t mode_press_tick = 0;

void display_replay_replay_mode(void)
{   
    if (display_editor_get_frame_magic() == DISPLAY_MAGIC)
    {
        frame = display_editor_get_frame_array(current_frame_index);
        
        for (uint8_t i = 0; i < LED_NUMBER; i++)
        {
            display_control_update_display(i, frame[i]);
        }
    }
    else
    {
        (void)hal_unique_id_get_id(unique_id, sizeof(unique_id));
        
        for (uint8_t i = 0; i < LED_NUMBER; i++)
        {
            fixed_frame[current_frame_index][i] = ((unique_id[i % 4] >> (i ^ current_frame_index) & 1u)) ? ON : OFF;
            display_control_update_display(i, fixed_frame[current_frame_index][i]);
        }
    }
    
    frame_timer = hal_timer_get_tick();
    
    if (frame_timer - previous_frame_timer > 4000)
    {
        previous_frame_timer = frame_timer;
        current_frame_index = (current_frame_index + 1) % MAX_FRAME_COUNT;
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
            lunokhod_switch_mode();
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
