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

void SysTick_Handler(void)
{
    callback();
}

hal_result_t hal_timer_init(hal_timer_init_t *init_struct)
{
    /* The SYSTICK calibration value is incorrect. Errata reference: 14157. 
     * The correct SYSTICK calibration value is 0x40000000. 
     * See 38.2.4 Device ATSAMD11 reference manual.*/

    const uint32_t reload_value = (DEFAULT_SYSTEM_CLOCK_HZ / init_struct->period) - 1u;

    /* SYSTICK using processor clock, enable tick interrupt. */
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);

    /* SYSTICK load value according to passed period. */
    SysTick->LOAD = reload_value;

    /* Assign callback if present. */
    if (init_struct->call_back)
    {
        callback = init_struct->call_back;
    }
    
    return HAL_SUCCESS;
}

hal_result_t hal_timer_clock_init(void)
{
    /* Uses default system clock. */
    return HAL_SUCCESS;
}

hal_result_t hal_timer_teardown(void)
{

}

hal_result_t hal_timer_clock_teardown(void)
{
    /* Uses default system clock. */
    return HAL_SUCCESS;
}

hal_result_t hal_timer_delay(uint16_t ms)
{

}

hal_result_t hal_timer_start(void)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

hal_result_t hal_timer_stop(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
