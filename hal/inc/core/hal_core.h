#ifndef HAL_CORE
#define HAL_CORE

/** \file
 * 
 * File containing result types that are returned from the HAL. 
 */

#include "../hal_result.h"

/** Initalise necessary clocks
 *
 *  
 */
hal_result_t hal_clock_init(void);

/**
 * 
 */
hal_result_t hal_clock_teardown(void);

#endif