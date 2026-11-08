/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "charlieplexing.h"

#include "hal_counter.h"
#include "hal_timer.h"
#include "hal_usb.h"
#include "hal_gpio.h"

#include "tusb.h"

#include "sam.h"

#include "usb_descriptors.h"

#define PORT_A_INDEX 0u
#define USB_ALTERNATE_FUNCTION_GROUP_G 6u

#define SAMD11_SWITCH_STEP   14u
#define SAMD11_SWITCH_TOGGLE 9u
#define SAMD11_SWITCH_PAGE   8u
#define SAMD11_SWITCH_MODE   7u

#define SAMD11_USB_DM 24u
#define SAMD11_USB_DP 25u

#define CHARLIEPLEXING_0 23u
#define CHARLIEPLEXING_1 22u
#define CHARLIEPLEXING_2 16u
#define CHARLIEPLEXING_3 15u

#define CHARLIEPLEX_LINES 4u

static uint8_t charlieplexed_pins[] = 
{
	CHARLIEPLEXING_0,
	CHARLIEPLEXING_1,
	CHARLIEPLEXING_2,
	CHARLIEPLEXING_3,
};

const hal_gpio_pin_t gpio_usb_dm =
{
	.pin = SAMD11_USB_DM,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_ALTERNATE,
};

const hal_gpio_pin_t gpio_usb_dp =
{
	.pin = SAMD11_USB_DP,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_ALTERNATE,
};

const hal_gpio_pin_t gpio_button_switch_step =
{
	.pin = SAMD11_SWITCH_STEP,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.trigger = HAL_GPIO_FALLING,
	.pull_up_mode = HAL_GPIO_PULL_UP
};

const hal_gpio_pin_t gpio_button_switch_toggle =
{
	.pin = SAMD11_SWITCH_TOGGLE,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.trigger = HAL_GPIO_FALLING,
	.pull_up_mode = HAL_GPIO_PULL_UP
};

const hal_gpio_pin_t gpio_button_switch_page =
{
	.pin = SAMD11_SWITCH_PAGE,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.trigger = HAL_GPIO_FALLING,
	.pull_up_mode = HAL_GPIO_PULL_UP
};

const hal_gpio_pin_t gpio_button_switch_mode =
{
	.pin = SAMD11_SWITCH_MODE,
	.port = PORT_A_INDEX,
	.pin_mode = HAL_GPIO_INPUT,
	.trigger = HAL_GPIO_FALLING,
	.pull_up_mode = HAL_GPIO_PULL_UP
};

const charlieplexed_led_t led_1 =
{
	.anode = CHARLIEPLEXING_0,
	.cathode = CHARLIEPLEXING_1
};

const charlieplexed_led_t led_2 =
{
	.anode = CHARLIEPLEXING_1,
	.cathode = CHARLIEPLEXING_2
};

const charlieplexed_led_t led_3 =
{
	.anode = CHARLIEPLEXING_2,
	.cathode = CHARLIEPLEXING_3
};

const charlieplexed_led_t led_4 =
{
	.anode = CHARLIEPLEXING_1,
	.cathode = CHARLIEPLEXING_0
};

const charlieplexed_led_t led_5 =
{
	.anode = CHARLIEPLEXING_1,
	.cathode = CHARLIEPLEXING_2
};

const charlieplexed_led_t led_6 =
{
	.anode = CHARLIEPLEXING_3,
	.cathode = CHARLIEPLEXING_2
};

const charlieplexed_led_t led_7 =
{
	.anode = CHARLIEPLEXING_0,
	.cathode = CHARLIEPLEXING_2
};

const charlieplexed_led_t led_8 =
{
	.anode = CHARLIEPLEXING_2,
	.cathode = CHARLIEPLEXING_0
};

const charlieplexed_led_t led_9 =
{
	.anode = CHARLIEPLEXING_1,
	.cathode = CHARLIEPLEXING_3
};

const charlieplexed_led_t led_10 =
{
	.anode = CHARLIEPLEXING_3,
	.cathode = CHARLIEPLEXING_1
};

const charlieplexed_led_t led_11 =
{
	.anode = CHARLIEPLEXING_0,
	.cathode = CHARLIEPLEXING_3
};

const charlieplexed_led_t led_12 =
{
	.anode = CHARLIEPLEXING_3,
	.cathode = CHARLIEPLEXING_0
};

static volatile bool key_pressed = false;

void button_callback(void)
{
	key_pressed = true;
}

static void board_init_gpio()
{
	hal_gpio_init_t dm_gpio =
	{
		.pin = gpio_usb_dm,
		.alternate_pin_mapping = USB_ALTERNATE_FUNCTION_GROUP_G,
	};
	
	hal_gpio_init_t dp_gpio =
	{
		.pin = gpio_usb_dp,
		.alternate_pin_mapping = USB_ALTERNATE_FUNCTION_GROUP_G,
	};

	hal_gpio_init_t gpio_switch_step =
	{
		.pin = gpio_button_switch_step,
		.trigger_event_cb = button_callback
	};
	
	hal_gpio_init_t gpio_switch_toggle =
	{
		.pin = gpio_button_switch_toggle,
		.trigger_event_cb = button_callback
	};
	
	hal_gpio_init_t gpio_switch_page =
	{
		.pin = gpio_button_switch_page,
		.trigger_event_cb = button_callback
	};
	
	hal_gpio_init_t gpio_switch_mode =
	{
		.pin = gpio_button_switch_mode,
		.trigger_event_cb = button_callback
	};
	
	(void)hal_gpio_pin_init(&dm_gpio);
	(void)hal_gpio_pin_init(&dp_gpio);
	(void)hal_gpio_pin_init(&gpio_switch_step);
	(void)hal_gpio_pin_init(&gpio_switch_toggle);
	(void)hal_gpio_pin_init(&gpio_switch_page);
	(void)hal_gpio_pin_init(&gpio_switch_mode);
	
	(void)charlieplexing_initialise_pin_table(charlieplexed_pins, CHARLIEPLEX_LINES);
}

void USB_Handler(void)
{
	tud_int_handler(0);
}

#define KEYS sizeof(keys)

static void counter_cb(void) 
{
}

/*------------- MAIN -------------*/
int main(void)
{
  //board_init();

  hal_timer_init_t init_struct =
  {
	  .period = 10,
	  .call_back = NULL
  };
  
  hal_usb_init_t usb_init =
  {
	  .external_clock = false
  };
  
  hal_counter_init_t counter_init = 
  {
	  .call_back = &counter_cb,
  };
  
  hal_usb_init(&usb_init);
  hal_usb_clock_init();

  hal_timer_init(&init_struct);
  hal_timer_start();
  
  hal_counter_clock_init();
  hal_counter_init(&counter_init);
  
  hal_counter_start();
  
  hal_gpio_clock_init();

  // init device stack on configured roothub port
  tusb_rhport_init_t dev_init = {.role = TUSB_ROLE_DEVICE, .speed = TUSB_SPEED_AUTO};
  tusb_init(BOARD_TUD_RHPORT, &dev_init);

  NVIC_SetPriority(USB_IRQn, 0);
  NVIC_EnableIRQ(USB_IRQn);

  board_init_gpio();

  bool button_was_pressed = false;
  
  uint8_t alphabet_index = 0;

	while (1)
	{
		tud_task(); // MUST run every single iteration without interruption
	}
}

uint32_t tusb_time_millis_api(void) 
{
	return hal_timer_get_tick();
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) {
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
	//blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
	(void)remote_wakeup_en;
	//blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
	//blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
}  

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void) 
{
	
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
	(void)itf;
	(void)rts;
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) 
{

}
