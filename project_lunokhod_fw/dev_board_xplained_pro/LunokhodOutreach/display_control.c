#include "charlieplexing.h"
#include "display_control.h"

#define CHARLIEPLEXING_0 23u
#define CHARLIEPLEXING_1 22u
#define CHARLIEPLEXING_2 16u
#define CHARLIEPLEXING_3 15u

#define CHARLIEPLEX_LINES 4u

#define LED_NUMBER        12u

typedef enum LED_STATE
{
    OFF,
    ON,
    FLASHING
} display_led_state_t;

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

static void flash_led_routine(void)
{
    
}

void initialise_display(void)
{
    (void)charlieplexing_initialise_pin_table(charlieplexed_pins, CHARLIEPLEX_LINES);
}

void display_tick(void)
{
    for (uint8_t i = 0; i < LED_NUMBER; i++)
    {
        switch (leds[i].led_state)
        {
            case OFF:
                /* Nothing to do here. */
                break;
            case ON:
                charlieplexing_set_pin_level(leds[i].led, HAL_GPIO_HIGH);
        }
    }
}
