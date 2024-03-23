#include "core/hal_core_interrupts.h"
#include "packs/Atmel.SAMD11_DFP.1.1.81/include/sam.h"

void hal_interrupts_enable()
{
    __enable_irq();
}

void hal_interrupts_disable()
{
    __disable_irq();
}
