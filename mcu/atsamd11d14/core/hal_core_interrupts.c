#include "hal_core_interrupts.h"
#include "sam.h"

void hal_interrupts_enable()
{
    __enable_irq();
}

void hal_interrupts_disable()
{
    __disable_irq();
}
