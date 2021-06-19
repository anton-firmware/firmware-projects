/*
 * GPIO.c
 *
 * Created: 05/06/2021 20:11:39
 *  Author: Anton
 */ 

#include "GPIO.h"

void GPIO_set_output(int pin)
{
	PORT->Group[0].DIRSET.reg |= pin;
}

void GPIO_output(int pin, uint8_t level)
{
	if(level)
	{
		PORT->Group[0].OUT.reg |= pin;
	}else
	{
		PORT->Group[0].OUT.reg &= ~pin;	
	}
}

void GPIO_set_input(int port, int pin)
{
	PORT->Group[0].PINCFG[pin].bit.INEN = 1; // enable input enable 
}

void GPIO_enable_pull_up(int port, int pin)
{
	PORT->Group[0].PINCFG[pin].bit.PULLEN = 1; // enable internal pull up
	PORT->Group[0].OUT.reg |= port;
}

int GPIO_read_input(int pin)
{
	return (PORT->Group[0].IN.reg & pin);
}