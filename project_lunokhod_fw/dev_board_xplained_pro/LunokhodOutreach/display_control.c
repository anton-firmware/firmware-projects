#include <stdbool.h>
#include <stdint.h>

#include "charlieplexing.h"
#include "display_control.h"
#include "hal_timer.h"

#define CHARLIEPLEXING_0 23u
#define CHARLIEPLEXING_1 22u
#define CHARLIEPLEXING_2 16u
#define CHARLIEPLEXING_3 15u

#define CHARLIEPLEX_LINES 4u

typedef enum FLASH_PHASE
{
    FLASH_PHASE_OFF,
    FLASH_PHASE_ON
} flash_phase_t;

typedef struct led_state 
{
    charlieplexed_led_t led;
    display_led_state_t led_state;
} display_led_info_t;

static uint8_t charlieplexed_pins[] =
{
    CHARLIEPLEXING_0,
    CHARLIEPLEXING_1,
    CHARLIEPLEXING_2,
    CHARLIEPLEXING_3,
};

/**
 * The LED array below matches the physical LED array ,
 * from left to right top to botton :
 * 
 * | LED 1 | LED 4  | LED 2  | LED 5  |
 * | LED 3 | LED 6  | LED 7  | LED 8  |
 * | LED 9 | LED 10 | LED 11 | LED 12 |
 */
static display_led_info_t leds[LED_NUMBER] =
{
    /* led_1 */
    {
        .led = { .anode = CHARLIEPLEXING_0, .cathode = CHARLIEPLEXING_1 },
        .led_state = OFF
    },
    /* led_4 */
    {
        .led = { .anode = CHARLIEPLEXING_1, .cathode = CHARLIEPLEXING_0 },
        .led_state = OFF
    },
    /* led_2 */
    {
        .led = { .anode = CHARLIEPLEXING_1, .cathode = CHARLIEPLEXING_2 },
        .led_state = OFF
    },
    /* led_5 */
    {
        .led = { .anode = CHARLIEPLEXING_2, .cathode = CHARLIEPLEXING_1 },
        .led_state = OFF
    },
    /* led_3 */
    {
        .led = { .anode = CHARLIEPLEXING_2, .cathode = CHARLIEPLEXING_3 },
        .led_state = OFF
    },
    /* led_6 */
    {
        .led = { .anode = CHARLIEPLEXING_3, .cathode = CHARLIEPLEXING_2 },
        .led_state = OFF
    },
    /* led_7 */
    {
        .led = { .anode = CHARLIEPLEXING_0, .cathode = CHARLIEPLEXING_2 },
        .led_state = OFF
    },
    /* led_8 */
    {
        .led = { .anode = CHARLIEPLEXING_2, .cathode = CHARLIEPLEXING_0 },
        .led_state = OFF
    },
    /* led_9 */
    {
        .led = { .anode = CHARLIEPLEXING_1, .cathode = CHARLIEPLEXING_3 },
        .led_state = OFF
    },
    /* led_10 */
    {
        .led = { .anode = CHARLIEPLEXING_3, .cathode = CHARLIEPLEXING_1 },
        .led_state = OFF
    },
    /* led_11 */
    {
        .led = { .anode = CHARLIEPLEXING_0, .cathode = CHARLIEPLEXING_3 },
        .led_state = OFF
    },
    /* led_12 */
    {
        .led = { .anode = CHARLIEPLEXING_3, .cathode = CHARLIEPLEXING_0 },
        .led_state = OFF
    },
};

static uint8_t current_led_index = 0;
static uint32_t timer_tick = 0;
static uint32_t previous_timer_tick = 0;
static flash_phase_t current_flash_phase = FLASH_PHASE_OFF;

static void flash_led_routine(uint8_t led_index)
{
    if (current_flash_phase == FLASH_PHASE_OFF)
    {
        charlieplexing_set_pin_level(leds[led_index].led, HAL_GPIO_LOW);
    }
    else
    {
        charlieplexing_set_pin_level(leds[led_index].led, HAL_GPIO_HIGH);
    }
}

void display_control_init_display(void)
{
    (void)charlieplexing_initialise_pin_table(charlieplexed_pins, CHARLIEPLEX_LINES);

    for (uint8_t i = 0; i < LED_NUMBER; i++)
    {   
        leds[i].led_state = OFF;
    }
}

display_led_state_t display_control_get_current_led_state(uint8_t led_index)
{
    return leds[led_index].led_state;
}

void display_control_update_display(uint8_t led_index, display_led_state_t state)
{
    leds[led_index].led_state = state;
}

void display_control_flash_single_led(uint8_t led_index)
{
    if (led_index < LED_NUMBER)
    {
        for (uint8_t i = 0; i < LED_NUMBER; i++)
        {
            if (leds[i].led_state == FLASHING)
            {
                leds[i].led_state = OFF;
            }
        }
        
        leds[led_index].led_state = FLASHING;
    }
}

void display_control_tick_display(void)
{
    current_led_index = (current_led_index + 1) % 12;
    timer_tick = hal_timer_get_tick();
 
    switch (current_flash_phase)
    {
        case FLASH_PHASE_OFF:
            if (timer_tick - previous_timer_tick > 25000)
            {
                previous_timer_tick = timer_tick;
                current_flash_phase = FLASH_PHASE_ON;
            }
            break;

        case FLASH_PHASE_ON:
            if (timer_tick - previous_timer_tick > 25000)
            {
                previous_timer_tick = timer_tick;
                current_flash_phase = FLASH_PHASE_OFF;
            }
            break;
    
        default:
            break;
    }

    switch (leds[current_led_index].led_state)
    {
        case OFF:
            charlieplexing_set_pin_level(leds[current_led_index].led, HAL_GPIO_LOW);
            break;

        case ON:
            charlieplexing_set_pin_level(leds[current_led_index].led, HAL_GPIO_HIGH);
            break; 

        case FLASHING:
            flash_led_routine(current_led_index);
            break;

        default:
            /* We shouldn't end up here... if we do, just cry. */
            break;
    }
}
