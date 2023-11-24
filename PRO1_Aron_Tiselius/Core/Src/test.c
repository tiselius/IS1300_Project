/*
 * test.c
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */

#include <variables.h>
#include "gpio.h"
#include "functions.h"

void tester(){
	//		led_test();
	//	car_sw_test();
	//		blinking();
	flag_tester();
}

void led_test(){
	shiftOut24(L1_Red);
	HAL_Delay(1000);
	shiftOut24(L1_Yellow + L1_Red);
	HAL_Delay(1000);
	shiftOut24(L1_Green);
	HAL_Delay(1000);

	shiftOut24(P1_Red);
	HAL_Delay(1000);
	shiftOut24(P1_Green);
	HAL_Delay(1000);
	shiftOut24(P1_Blue);
	HAL_Delay(1000);

	shiftOut24(L2_Red);
	HAL_Delay(1000);
	shiftOut24(L2_Yellow);
	HAL_Delay(1000);
	shiftOut24(L2_Green);
	HAL_Delay(1000);

	shiftOut24(P2_Red);
	HAL_Delay(1000);
	shiftOut24(P2_Green);
	HAL_Delay(1000);
	shiftOut24(P2_Blue);
	HAL_Delay(1000);

	shiftOut24(L3_Red);
	HAL_Delay(1000);
	shiftOut24(L3_Yellow);
	HAL_Delay(1000);
	shiftOut24(L3_Green);
	HAL_Delay(1000);

	shiftOut24(L4_Red);
	HAL_Delay(1000);
	shiftOut24(L4_Yellow);
	HAL_Delay(1000);
	shiftOut24(L4_Green);
	HAL_Delay(1000);
}

void car_sw_test(){
	while(HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 1){
		shiftOut24(0);
	}
	shiftOut24(P1_Red);
	HAL_Delay(1000);
}

void blinking(){
	while(1){
		blink_led(L1_Red);
		blink_led(L1_Red);
		blink_led(L1_Yellow);
		blink_led(L1_Yellow);
		blink_led(L1_Green);
		blink_led(L1_Green);
		blink_led(L2_Red);
		blink_led(L2_Red);
		blink_led(L2_Yellow);
		blink_led(L2_Yellow);
		blink_led(L2_Green);
		blink_led(L2_Green);
		blink_led(L3_Red);
		blink_led(L3_Red);
		blink_led(L3_Yellow);
		blink_led(L3_Yellow);
		blink_led(L3_Green);
		blink_led(L3_Green);
		blink_led(L4_Red);
		blink_led(L4_Red);
		blink_led(L4_Yellow);
		blink_led(L4_Yellow);
		blink_led(L4_Green);
		blink_led(L4_Green);

		blink_led(P1_Red);
		blink_led(P1_Red);
		blink_led(P1_Green);
		blink_led(P1_Green);
		blink_led(P1_Blue);
		blink_led(P1_Blue);
		blink_led(P2_Red);
		blink_led(P2_Red);
		blink_led(P2_Green);
		blink_led(P2_Green);
		blink_led(P2_Blue);
		blink_led(P2_Blue);
	}
}


void flag_tester(){
	if(TL1_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L1_Green);
		TL1_Car_Flag = 0;
	}

	if(TL2_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L2_Green);
		TL2_Car_Flag = 0;
	}

	if(TL3_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L3_Green);
		TL3_Car_Flag = 0;
	}

	if(TL4_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L4_Green);
		TL4_Car_Flag = 0;
	}

	if(PL1_Switch_Flag == 1)
		for(int i = 0; i<10; i++)
			blink_led(P1_Blue);
	PL1_Switch_Flag = 0;

	if(PL2_Switch_Flag == 1)
		for(int i = 0; i<10; i++)
			blink_led(P2_Blue);
	PL2_Switch_Flag = 0;
}

