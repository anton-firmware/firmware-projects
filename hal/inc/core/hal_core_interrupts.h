#ifndef HAL_CORE_INTERRUPTS_H
#define HAL_CORE_INTERRUPTS_H

/** \file
 * 
 * File containing functions related to global interrupt operation.
 */

/** Enable global interrupts. */
void hal_interrupts_enable(void);

/** Disable global interrupts. */
void hal_interrupts_disable(void);

#endif