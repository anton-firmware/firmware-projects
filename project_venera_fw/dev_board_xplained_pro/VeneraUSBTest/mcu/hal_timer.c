/** \file
 *
 * Implementation for HAL timer peripheral.
 * 
 * \warning Currently only supports a simple timer on SYSTICK.
 */

#include <stdbool.h>
#include <stdint.h>

#include "hal_timer.h"
#include "sam.h"

#define DEFAULT_SYSTEM_CLOCK_HZ 1000000u

static hal_timer_event_cb_t callback;
static volatile uint32_t sys_tick_count;
static uint32_t period;

void SysTick_Handler(void)
{
    if (callback)
    {
        callback();
    }

    sys_tick_count++;
}

hal_result_t hal_timer_init(hal_timer_init_t *init_struct)
{
    /* The SYSTICK calibration value is incorrect. Errata reference: 14157. 
     * The correct SYSTICK calibration value is 0x40000000. 
     * See 38.2.4 Device ATSAMD11 reference manual.*/

    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    /* Timer period of 0 is invalid. */
    if (init_struct->period != 0)
    {
        period = init_struct->period;
        const uint32_t reload_value = (DEFAULT_SYSTEM_CLOCK_HZ / (1000u / period)) - 1u;

        /* SYSTICK using processor clock, enable tick interrupt. */
        SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);

        /* SYSTICK load value according to passed period. */
        SysTick->LOAD = reload_value;

        /* Reset the SysTick to 0. */
        SysTick->VAL = 0;

        /* Assign callback if present. */
        if (init_struct->call_back)
        {
            callback = init_struct->call_back;
        }

        result =  HAL_SUCCESS;
    }
    
    return result;
}

hal_result_t hal_timer_clock_init(void)
{
    /* Uses default system clock. */
    return HAL_SUCCESS;
}

hal_result_t hal_timer_teardown(void)
{
    /* Make sure the timer is disabled. */
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    /* Return clock source and disable interrupt. */
    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);
}

hal_result_t hal_timer_clock_teardown(void)
{
    /* Uses default system clock. */
    return HAL_SUCCESS;
}

hal_result_t hal_timer_delay(uint16_t ms)
{
    uint32_t start = sys_tick_count;
    uint32_t ticks_in_delay = ((ms * period) / 1000u);

    while ((sys_tick_count - start) < ticks_in_delay)
    {
        /* Blocking delay. */
    }
}

uint32_t hal_timer_get_tick(void)
{
	return sys_tick_count;
}

hal_result_t hal_timer_start(void)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

hal_result_t hal_timer_stop(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
