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

// /** Structure representing timer initialisation. */
// typedef struct hal_timer_init
// {
//     uint16_t             period;    /*!< The period of the timer in seconds. */
//     hal_timer_event_cb_t call_back; /*!< Callback for timer tick. */

// } hal_timer_init_t;

hal_result_t hal_timer_init(hal_timer_init_t *init_struct)
{
    /* The SYSTICK calibration value is incorrect. Errata reference: 14157. 
     * The correct SYSTICK calibration value is 0x40000000. 
     * See 38.2.4 Device ATSAMD11 reference manual.*/

    /* SYSTICK using processor clock. */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
}

hal_result_t hal_timer_clock_init(void)
{

}

hal_result_t hal_timer_teardown(void)
{

}

hal_result_t hal_timer_clock_teardown(void)
{

}

hal_result_t hal_timer_delay(uint16_t ms)
{

}

hal_result_t hal_timer_start(void)
{

}

hal_result_t hal_timer_stop(void)
{

}
