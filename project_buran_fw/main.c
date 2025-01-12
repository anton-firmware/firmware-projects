/*
 * Test.c
 *
 * Created: 04/04/2024 21:12:29
 * Author : Anton
 */ 


#include "sam.h"
#include "hal_gpio.h"
#include "hal_serial.h"
#include "hal_timer.h"

#define PORT_A 0

#define USART_TX_PA22 22u
#define USART_RX_PA23 23u

#define MCU_LED_1_PA5 5u
#define MCU_LED_2_PA6 6u
#define MCU_LED_PA16 16u

#define MCU_SWITCH_1_PA25 25u

#define USART_GROUP_C_ALT 0x2 // SERCOM Pad is in Group C, see Table 6-1 PORT Function Multiplexing.

#define BURAN_TASK_LED_1_TOGGLE   'A'
#define BURAN_TASK_LED_2_TOGGLE   'B'
#define BURAN_TASK_PRINT_VERSION  'C'

static volatile uint8_t task;
const uint8_t VERSION[] = "Project Buran v3.0\n";

hal_gpio_pin_t gpio_pin_button_sw1 =
{
	.pin = MCU_SWITCH_1_PA25,
	.port = PORT_A,
	.pin_mode = HAL_GPIO_INPUT,
};

hal_gpio_pin_t gpio_pin_led_16 =
{
	.pin = MCU_LED_PA16,
	.port = PORT_A,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

hal_gpio_pin_t gpio_pin_tx =
{
	.pin = USART_TX_PA22,
	.port = PORT_A,
	.pin_mode = HAL_GPIO_ALTERNATE,
};

hal_gpio_pin_t gpio_pin_rx =
{
	.pin = USART_RX_PA23,
	.port = PORT_A,
	.pin_mode = HAL_GPIO_ALTERNATE,
};

hal_gpio_pin_t gpio_pin_led_1 =
{
	.pin = MCU_LED_1_PA5,
	.port = PORT_A,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

hal_gpio_pin_t gpio_pin_led_2 =
{
	.pin = MCU_LED_2_PA6,
	.port = PORT_A,
	.pin_mode = HAL_GPIO_OUTPUT_PUSH_PULL,
};

static void read_callback(uint8_t byte)
{
	task = byte;
}

static void timer_callback(void)
{
}

int main(void)
 {
    /* Initialize the SAM system */
    SystemInit();
	
	hal_gpio_init_t init_struct_tx = 
	{
		.pin = gpio_pin_tx,	
		.alternate_pin_mapping = USART_GROUP_C_ALT,
	};
	
	hal_gpio_init_t init_struct_rx =
	{
		.pin = gpio_pin_rx,
		.alternate_pin_mapping = USART_GROUP_C_ALT,
	};
	
	hal_gpio_init_t init_struct_led_1 =
	{
		.pin = gpio_pin_led_1,
	};
	
	hal_gpio_init_t init_struct_led_2 =
	{
		.pin = gpio_pin_led_2,
	};
	
	hal_gpio_init_t init_struct_led_16 =
	{
		.pin = gpio_pin_led_16,
	};
	
	hal_gpio_init_t init_struct_button_sw1 =
	{
		.pin = gpio_pin_button_sw1,
	};
	
	hal_gpio_pin_init(&init_struct_tx);
	hal_gpio_pin_init(&init_struct_rx);
	hal_gpio_pin_init(&init_struct_led_1);
	hal_gpio_pin_init(&init_struct_led_2);
	hal_gpio_pin_init(&init_struct_led_16);
	hal_gpio_pin_init(&init_struct_button_sw1);
	
	hal_serial_init_t init_struct_hal = 
	{
		.mode = HAL_SERIAL_MODE_RX_TX,
		.stop_bits = HAL_SERIAL_STOP_BITS_ONE,
		.parity_bits = HAL_SERIAL_PARITY_BITS_NONE,
		.baud_rate = HAL_SERIAL_BAUD_RATE_9600,
		.read_event_cb = read_callback,
	};
	
	hal_timer_init_t init_struct_timer = 
	{
		.period = 1u,
		.call_back = timer_callback
	};
	
	hal_serial_clock_init();
	hal_timer_init(&init_struct_timer);
	
	hal_timer_start();
	hal_serial_init(&init_struct_hal);

    while (1) 
    {
		if (task == BURAN_TASK_LED_1_TOGGLE)
		{
			hal_gpio_toggle_level(&gpio_pin_led_1);
			task = 0;
		}
		else if (task == BURAN_TASK_LED_2_TOGGLE)
		{
			hal_gpio_toggle_level(&gpio_pin_led_2);
			task = 0;
		}
		else if (task == BURAN_TASK_PRINT_VERSION)
		{
			hal_serial_transmit_non_blocking(VERSION, sizeof(VERSION));
			task = 0;
		}
		
		if (!hal_gpio_read_level(&gpio_pin_button_sw1))
		{
			hal_timer_delay(1000);
			
			if (!hal_gpio_read_level(&gpio_pin_button_sw1))
			{
				hal_gpio_toggle_level(&gpio_pin_led_1);
			}
		}
    }
}
