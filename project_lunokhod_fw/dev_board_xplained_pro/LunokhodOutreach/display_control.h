#ifndef DISPLAY_CONTROL_H
#define DISPLAY_CONTROL_H

#include <stdint.h>

#define LED_NUMBER        12u

typedef enum LED_STATE
{
    OFF,
    ON,
    FLASHING
} __attribute__((packed)) display_led_state_t;

void display_control_init_display(void);

void display_control_tick_display(void);

display_led_state_t display_control_get_current_led_state(uint8_t led_index);

void display_control_flash_all(void);

void display_control_update_display(uint8_t led_index, display_led_state_t state);

void display_control_flash_single_led(uint8_t led_index);

#endif /* DISPLAY_CONTROL_H */
