/*
 * buran.h
 *
 * Definitions of pins for the Buran PCB.
 * 
 * Created: 12/01/2025 00:20:17
 *  Author: Anton
 */ 

 
#ifndef BURAN_H
#define BURAN_H

#include "hal_result.h"
#include "hal_gpio.h"

#define BURAN_PORT_A_INDEX      0u
#define BURAN_USART_GROUP_C_ALT 2u /* SERCOM Pad is in Group C, see Table 6-1 PORT Function Multiplexing. */

#define BURAN_DEBUG_LED_1_PIN   5u
#define BURAN_DEBUG_LED_2_PIN   6u

#define BURAN_DEBUG_1_PIN       16u
#define BURAN_DEBUG_2_PIN       9u
#define BURAN_DEBUG_3_PIN       8u
#define BURAN_DEBUG_4_PIN       7u
#define BURAN_DEBUG_5_PIN       4u

#define BURAN_SWITCH_1_PIN      25u
#define BURAN_SWITCH_2_PIN      24u
#define BURAN_SWITCH_3_PIN      2u
#define BURAN_SWITCH_4_PIN      3u

#define BURAN_USART_TX_PIN      22u
#define BURAN_USART_RX_PIN      23u

extern const hal_gpio_pin_t buran_gpio_pin_button_switch_1;
extern const hal_gpio_pin_t buran_gpio_pin_button_switch_2;
extern const hal_gpio_pin_t buran_gpio_pin_button_switch_3;
extern const hal_gpio_pin_t buran_gpio_pin_button_switch_4;
extern const hal_gpio_pin_t buran_gpio_pin_debug_1;
extern const hal_gpio_pin_t buran_gpio_pin_debug_2;
extern const hal_gpio_pin_t buran_gpio_pin_debug_3;
extern const hal_gpio_pin_t buran_gpio_pin_debug_4;
extern const hal_gpio_pin_t buran_gpio_pin_debug_5;
extern const hal_gpio_pin_t buran_gpio_pin_led_1;
extern const hal_gpio_pin_t buran_gpio_pin_led_2;
extern const hal_gpio_pin_t buran_gpio_pin_tx;
extern const hal_gpio_pin_t buran_gpio_pin_rx;

#endif /* BURAN_H_ */
