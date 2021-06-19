/*
 * GPIO.h
 *
 * Created: 05/06/2021 19:09:16
 *  Author: Anton
 * Basic GPIO library for ATSAMD11 for use in Project Buran FW
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "main.h"

void GPIO_output(int pin, uint8_t level);
void GPIO_clear_output(int pin);
void GPIO_set_output(int pin);

void GPIO_set_input(int port, int pin);
void GPIO_enable_pull_up(int port, int pin);
int GPIO_read_input(int pin); 

#endif /* GPIO_H_ */