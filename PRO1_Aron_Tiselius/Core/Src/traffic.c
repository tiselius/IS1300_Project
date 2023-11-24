/*
 * traffic.c
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */
#include <variables.h>
#include "functions.h"

void traffic_start(){
	traffic_init();
	while(0){
		blink_led(P1_Blue);
	}
	setLeds(P2_Green);
	HAL_Delay(1000);
	resetLeds(P2_Green);
	HAL_Delay(1000);
	setLeds(P2_Green + L2_Yellow + L3_Yellow + L1_Red);
	HAL_Delay(1000);
	while(1){}

}
