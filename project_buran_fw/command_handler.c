/*
 * command_handler.c
 *
 * Created: 26/01/2025 18:31:16
 *  Author: Anton
 */ 

#include <stdio.h>

#include "buran.h"
#include "command_handler.h"
#include "hal_gpio.h"
#include "hal_serial.h"
#include "sam.h"

#define VERSION_LEGNTH              32u

#define BURAN_COMMAND_IDENTIFY      'I'
#define BURAN_COMMAND_VERSION       'V'
#define BURAN_COMMAND_BUTTONS       'B'
#define BURAN_COMMAND_LED_1_TOGGLE  'Q'
#define BURAN_COMMAND_LED_2_TOGGLE  'W'
#define BURAN_COMMAND_RESET         'R'

static const uint8_t command_handler_invalid[] = "Invalid command received!\r\n";
static const uint8_t command_handler_identify[] = "BuranPCB\r\n";
static const uint8_t command_handler_version_string[] = "Buran2025V1\r\n";
static const uint8_t button_supported_string[] = "Buran4Buttons\r\n";
static const uint8_t button_reset_string[] = "BuranReset\r\n";

void buran_command_handler(uint8_t byte)
{
	char byte_rx = (char)byte;
	
	switch (byte_rx)
	{
		case BURAN_COMMAND_RESET:
			hal_serial_transmit_blocking(button_reset_string, sizeof(button_reset_string));
			NVIC_SystemReset();
			break;
		
		case BURAN_COMMAND_LED_2_TOGGLE:
			hal_gpio_toggle_level(&buran_gpio_pin_led_2);
			break;
		
		case BURAN_COMMAND_LED_1_TOGGLE:
			hal_gpio_toggle_level(&buran_gpio_pin_led_1);
			break;
		
		case BURAN_COMMAND_BUTTONS:
			hal_serial_transmit_non_blocking(button_supported_string, sizeof(button_supported_string));
			break;
			
		case BURAN_COMMAND_VERSION:
			hal_serial_transmit_non_blocking(command_handler_version_string, sizeof(command_handler_version_string));
			break;
		
		case BURAN_COMMAND_IDENTIFY:
			hal_serial_transmit_non_blocking(command_handler_identify, sizeof(command_handler_identify));
			break;
			
		default:
			hal_serial_transmit_non_blocking(command_handler_invalid, sizeof(command_handler_invalid));
			break;
	}
}