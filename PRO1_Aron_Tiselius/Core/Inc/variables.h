/*
 * led_variables.h
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */
#include "gpio.h"

#ifndef INC_LED_VARIABLES_H_
#define INC_LED_VARIABLES_H_

	/* LED NAMES */
	extern uint8_t L1_Red;
	extern uint8_t L1_Yellow;
	extern uint8_t L1_Green;

	extern uint8_t P1_Red;
	extern uint8_t P1_Green;
	extern uint8_t P1_Blue;

	extern uint16_t P2_Red;
	extern uint16_t P2_Green;
	extern uint16_t P2_Blue;

	extern uint16_t L2_Red;
	extern uint16_t L2_Yellow;
	extern uint16_t L2_Green;

	extern uint32_t L3_Red;
	extern uint32_t L3_Yellow;
	extern uint32_t L3_Green;

	extern uint32_t L4_Red;
	extern uint32_t L4_Yellow;
	extern uint32_t L4_Green;

	/* FLAGS */
	extern volatile uint8_t TL1_Car_Flag;
	extern volatile uint8_t TL2_Car_Flag;
	extern volatile uint8_t TL3_Car_Flag;
	extern volatile uint8_t TL4_Car_Flag;

	extern volatile uint8_t PL1_Switch_Flag;
	extern volatile uint8_t PL2_Switch_Flag;

	/* LIGHT DELAYS, FREQUENCIES */
	extern uint8_t toggleFreq;
	extern uint8_t pedestrianDelay;
	extern uint8_t walkingDelay;
	extern uint8_t orangeDelay;

	/* Other */
	extern volatile uint32_t test;


#endif /* INC_LED_VARIABLES_H_ */
