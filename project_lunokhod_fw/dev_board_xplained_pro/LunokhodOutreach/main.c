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

#include "display_control.h"
#include "display_editor.h"
#include "display_replay.h"
#include "hal_core_unique_id.h"
#include "hal_counter.h"
#include "hal_flash.h"
#include "hal_timer.h"
#include "hal_usb.h"
#include "hal_gpio.h"
#include "main.h"
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

#define BUTTON_COUNT      4u
#define BUTTON_DEBOUNCE_LIMIT 100u

#define STEP_BUTTON_INDEX   0u
#define TOGGLE_BUTTON_INDEX 1u
#define PAGE_BUTTON_INDEX   2u
#define MODE_BUTTON_INDEX   3u

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

static uint32_t tick_timer = 0;
static bool edit_mode = true;

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
    };
    
    hal_gpio_init_t gpio_switch_toggle =
    {
        .pin = gpio_button_switch_toggle,
    };
    
    hal_gpio_init_t gpio_switch_page =
    {
        .pin = gpio_button_switch_page,
    };
    
    hal_gpio_init_t gpio_switch_mode =
    {
        .pin = gpio_button_switch_mode,
    };
    
    (void)hal_gpio_pin_init(&dm_gpio);
    (void)hal_gpio_pin_init(&dp_gpio);

    (void)hal_gpio_pin_init(&gpio_switch_step);
    (void)hal_gpio_pin_init(&gpio_switch_toggle);
    (void)hal_gpio_pin_init(&gpio_switch_page);
    (void)hal_gpio_pin_init(&gpio_switch_mode);
}

void USB_Handler(void)
{
    tud_int_handler(0);
}

static void counter_cb(void)
{
}

static void timer_cb(void)
{
    if ((tick_timer++ % 10) == 0 )
    {
        display_control_tick_display();
    }
}

hal_gpio_level_t read_gpio_debounced(hal_gpio_pin_t pin)
{
    if (hal_gpio_read_level(&pin) == HAL_GPIO_LOW)
    {
        hal_timer_delay(10);

        if (hal_gpio_read_level(&pin) == HAL_GPIO_LOW)
        {
            return HAL_GPIO_LOW;
        }
    }

    return HAL_GPIO_HIGH;
}

void lunokhod_switch_mode(void)
{
    edit_mode = !edit_mode;
}

int main(void)
{
    hal_timer_init_t init_struct =
    {
        .period = 10,
        .call_back = timer_cb
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
    
    hal_counter_clock_init();
    hal_counter_init(&counter_init);
    
    hal_counter_start();
    
    hal_gpio_clock_init();

    tusb_rhport_init_t dev_init = {.role = TUSB_ROLE_DEVICE, .speed = TUSB_SPEED_AUTO};
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    NVIC_SetPriority(USB_IRQn, 0);
    NVIC_EnableIRQ(USB_IRQn);

    board_init_gpio();
    display_control_init_display();
    
    hal_timer_start();
    
    display_editor_load_from_flash();
    
    while (1)
    {
        if (edit_mode)
        {
            display_editor_edit_mode();
        }
        else 
        {
            display_replay_replay_mode();
        }
        
        tud_task();
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
void tud_mount_cb(void)
{

}

// Invoked when device is unmounted
void tud_umount_cb(void)
{

}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf)
{

}
