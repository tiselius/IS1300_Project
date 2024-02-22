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

void setLeds(uint32_t leds);
void resetLeds(uint32_t leds);

void blink_led(uint32_t leds);
void pedestrian_blink_led(uint32_t leds,uint32_t time);

void trafficOnNS();
void trafficOffNS();

void trafficOnEW();
void trafficOffEW();

void trafficTransition();
void trafficTransitiontest();

void pedestrianOnNS();
void pedestrianOffNS();

void pedestrianOnEW();
void pedestrianOffEW();

#endif /* INC_FUNCTIONS_H_ */
