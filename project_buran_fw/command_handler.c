/*
 * command_handler.c
 *
 * Created: 26/01/2025 18:31:16
 *  Author: Anton
 */ 

#include "command_handler.h"
#include "hal_serial.h"

#define BURAN_COMMAND_IDENTIFY      'I'
#define BURAN_COMMAND_VERSION       'V'
#define BURAN_COMMAND_BUTTONS       'B'
#define BURAN_COMMAND_LED_1_TOGGLE  'Q'

const uint8_t command_handler_invalid[] = "Invalid command received!\r\n";
const uint8_t command_handler_identify[] = "ProjectBuranPCB\r\n";

void buran_command_handler(uint8_t byte)
{
	char byte_rx = (char)byte;
	
	switch (byte_rx)
	{
		case BURAN_COMMAND_IDENTIFY:
			hal_serial_transmit_non_blocking(command_handler_identify, sizeof(command_handler_identify));
			break;
		default:
			hal_serial_transmit_non_blocking(command_handler_invalid, sizeof(command_handler_invalid));
			break;
	}
}