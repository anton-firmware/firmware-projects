/*
 * main.h
 *
 * Created: 21/11/2026 20:48:12
 *  Author: bisho
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "hal_core_unique_id.h"
#include "hal_gpio.h"

typedef enum button_phase
{
    UNPRESSED,
    PROCESSING_SHORT,
    PROCESSING_LONG,
    PROCESSING_COMBINED,
    PRESSED
} button_phase_t;

extern const hal_gpio_pin_t gpio_button_switch_step;
extern const hal_gpio_pin_t gpio_button_switch_toggle;
extern const hal_gpio_pin_t gpio_button_switch_page;
extern const hal_gpio_pin_t gpio_button_switch_mode;

extern uint32_t config_row_start;

hal_gpio_level_t read_gpio_debounced(hal_gpio_pin_t pin);

void lunokhod_switch_mode(void);

#endif /* MAIN_H_ */
