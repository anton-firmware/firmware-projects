/*
 * buran.c
 *
 * Created: 26/01/2025 10:31:33
 *  Author: Anton
 */ 

#include "buran.h"
#include "hal_result.h"

const hal_gpio_pin_t buran_gpio_pin_button_switch_1 =
{
	.pin = BURAN_SWITCH_1_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.pull_up_mode = HAL_GPIO_PULL_UP,
	.trigger = HAL_GPIO_FALLING,
};

const hal_gpio_pin_t buran_gpio_pin_button_switch_2 =
{
	.pin = BURAN_SWITCH_2_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.pull_up_mode = HAL_GPIO_PULL_UP,
	.trigger = HAL_GPIO_FALLING,
};

const hal_gpio_pin_t buran_gpio_pin_button_switch_3 =
{
	.pin = BURAN_SWITCH_3_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.pull_up_mode = HAL_GPIO_PULL_UP,
	.trigger = HAL_GPIO_FALLING,
};

const hal_gpio_pin_t buran_gpio_pin_button_switch_4 =
{
	.pin = BURAN_SWITCH_4_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.pull_up_mode = HAL_GPIO_PULL_UP,
	.trigger = HAL_GPIO_FALLING,
};

const hal_gpio_pin_t buran_gpio_pin_debug_1 =
{
	.pin = BURAN_DEBUG_1_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_debug_2 =
{
	.pin = BURAN_DEBUG_2_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_debug_3 =
{
	.pin = BURAN_DEBUG_3_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_debug_4 =
{
	.pin = BURAN_DEBUG_4_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_debug_5 =
{
	.pin = BURAN_DEBUG_5_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_led_1 =
{
	.pin = BURAN_DEBUG_LED_1_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_led_2 =
{
	.pin = BURAN_DEBUG_LED_2_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

const hal_gpio_pin_t buran_gpio_pin_tx =
{
	.pin = BURAN_USART_TX_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_ALTERNATE,
};

const hal_gpio_pin_t buran_gpio_pin_rx =
{
	.pin = BURAN_USART_RX_PIN,
	.port = BURAN_PORT_A_INDEX,
	.pin_mode = HAL_GPIO_ALTERNATE,
};
