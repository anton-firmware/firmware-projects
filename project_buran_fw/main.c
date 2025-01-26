/*
 * Test.c
 *
 * Created: 04/04/2024 21:12:29
 * Author : Anton
 */ 

#include "buran.h"
#include "event_queue.h"
#include "hal_core_interrupts.h"
#include "hal_gpio.h"
#include "hal_serial.h"
#include "hal_timer.h"
#include "hal_result.h"
#include "sam.h"

#define EVENT_QUEUE_SIZE          100u

static event_t event_queue[EVENT_QUEUE_SIZE];

static void buran_callback_serial(void)
{
	
}

static void buran_callback_switch_1(void)
{
	
}

static void buran_callback_switch_2(void)
{
	
}

static void buran_callback_switch_3(void)
{
	
}

static void buran_callback_switch_4(void)
{
	
}

static void buran_timer_init(void)
{
	hal_timer_init_t init_struct_timer =
	{
		.period = 10u,
	};

	hal_timer_init(&init_struct_timer);
	
	hal_timer_start();	
}

static void buran_serial_init(void)
{
	hal_serial_init_t init_struct_hal =
	{
		.mode = HAL_SERIAL_MODE_RX_TX,
		.stop_bits = HAL_SERIAL_STOP_BITS_ONE,
		.parity_bits = HAL_SERIAL_PARITY_BITS_NONE,
		.baud_rate = HAL_SERIAL_BAUD_RATE_9600,
		.read_event_cb = buran_callback_serial,
	};
	
	hal_serial_init(&init_struct_hal);	
}

static void buran_gpio_init(void)
{
	hal_gpio_init_t init_struct_tx =
	{
		.pin = buran_gpio_pin_tx,
		.alternate_pin_mapping = BURAN_USART_GROUP_C_ALT,
	};
	
	hal_gpio_init_t init_struct_rx =
	{
		.pin = buran_gpio_pin_rx,
		.alternate_pin_mapping = BURAN_USART_GROUP_C_ALT,
	};
	
	hal_gpio_init_t init_struct_led_1 =
	{
		.pin = buran_gpio_pin_led_1,
	};
	
	hal_gpio_init_t init_struct_led_2 =
	{
		.pin = buran_gpio_pin_led_2,
	};
	
	hal_gpio_init_t init_struct_button_switch_1 =
	{
		.pin = buran_gpio_pin_button_switch_1,
		.trigger_event_cb = buran_callback_switch_1,
	};
	
	hal_gpio_init_t init_struct_button_switch_2 =
	{
		.pin = buran_gpio_pin_button_switch_2,
		.trigger_event_cb = buran_callback_switch_2,
	};
	
	hal_gpio_init_t init_struct_button_switch_3 =
	{
		.pin = buran_gpio_pin_button_switch_3,
		.trigger_event_cb = buran_callback_switch_3,
	};
	
	hal_gpio_init_t init_struct_button_switch_4 =
	{
		.pin = buran_gpio_pin_button_switch_4,
		.trigger_event_cb = buran_callback_switch_4,
	};
	
	hal_gpio_pin_init(&init_struct_tx);
	hal_gpio_pin_init(&init_struct_rx);
	hal_gpio_pin_init(&init_struct_led_1);
	hal_gpio_pin_init(&init_struct_led_2);
	hal_gpio_pin_init(&init_struct_button_switch_1);
	hal_gpio_pin_init(&init_struct_button_switch_2);
	hal_gpio_pin_init(&init_struct_button_switch_3);
	hal_gpio_pin_init(&init_struct_button_switch_4);
}

int main(void)
 {
    /* Initialize the SAM system */
    SystemInit();
	
	hal_gpio_clock_init();
	hal_serial_clock_init();
	
	buran_gpio_init();
	buran_serial_init();
	buran_timer_init();
	
	event_queue_initialise(event_queue, EVENT_QUEUE_SIZE);
	
	event_t dequeued_event;

    while (1) 
    {
		if (event_queue_dequeue_critical(&dequeued_event))
		{
			switch (dequeued_event.id)
			{
				default:
					break;
			}
		}
		
    }
}
