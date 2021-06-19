/*
 * project_buran_fw.c
 *
 * Created: 05/06/2021 19:08:34
 * Author : Anton
 */ 


#include "sam.h"
#include "main.h"

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	init_GPIO_switches();
	i2c_configure();
	i2c_read();
	
    /* Replace with your application code */
	
    while (1) 
	{
		GPIO_output(PORT_PA23, true);
	}
}

void init_GPIO_switches()
{
	GPIO_set_output(PORT_PA23);
	GPIO_set_output(PORT_PA22);
	
	GPIO_set_input(PORT_PA05, PIN_PA05);
	GPIO_set_input(PORT_PA06, PIN_PA06);
	GPIO_set_input(PORT_PA07, PIN_PA07);
	GPIO_set_input(PORT_PA16, PIN_PA16);
	
	GPIO_enable_pull_up(PORT_PA05, PIN_PA05);
	GPIO_enable_pull_up(PORT_PA06, PIN_PA06);
	GPIO_enable_pull_up(PORT_PA07, PIN_PA07);
	GPIO_enable_pull_up(PORT_PA16, PIN_PA16);
}