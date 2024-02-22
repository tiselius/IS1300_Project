/**
******************************************************************************
@brief
@file
@author
@version 1.0
@date 12-August-2019
@brief Functions and structures for program Pingpong
******************************************************************************
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

	/* Combined lights*/
	extern uint32_t NSTrafficGreen;
	extern uint32_t NSTrafficYellow;
	extern uint32_t NSTrafficRed;

	extern uint32_t EWTrafficGreen;
	extern uint32_t EWTrafficYellow;
	extern uint32_t EWTrafficRed;

	extern uint32_t NSCrossingActive;
	extern uint32_t EWCrossingActive;

	/* Switch and Car FLAGS */
	extern volatile uint8_t TL1_Car_Flag;
	extern volatile uint8_t TL2_Car_Flag;
	extern volatile uint8_t TL3_Car_Flag;
	extern volatile uint8_t TL4_Car_Flag;

	extern volatile uint8_t PL1_Switch_Flag;
	extern volatile uint8_t PL2_Switch_Flag;


	/*Light Flags*/
	extern uint8_t NSTrafficFlag;
	extern uint8_t EWTrafficFlag;
	extern uint8_t NSPedestrianFlag;
	extern uint8_t EWPedestrianFlag;

	extern uint8_t NSPedTransitioning;
	extern uint8_t EWPedTransitioning;

	/* LIGHT DELAYS, FREQUENCIES */
	extern uint8_t toggleFreq;
	extern uint16_t pedestrianDelay;
	extern uint16_t walkingDelay;
	extern uint16_t orangeDelay;
	extern uint16_t greenDelay;
	extern uint16_t redDelayMax;


	/* Other */
	extern uint32_t currentData;


#endif /* INC_LED_VARIABLES_H_ */
