/*
 * functions.h
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_
#include "gpio.h"

void shiftOutbyte(uint32_t data);
void shiftOut24(uint32_t data);
extern uint32_t currentData;

void traffic_init();

void setLeds(uint32_t leds);
void resetLeds(uint32_t leds);

void blink_led(uint32_t leds);

#endif /* INC_FUNCTIONS_H_ */
