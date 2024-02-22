/*
 * test.c
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */

#include <variables.h>
#include "gpio.h"
#include "functions.h"
#include "test.h"

void tester(){
	//			led_test();
	//		car_sw_test();
	//			blinking();
	//		flag_tester();
	//	timer_tester();
	//	traffic_sequence();
	pedestrian_test();
}

/*Simple test for shiftOut24*/
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
	shiftOut24(0xFFFFFF);
}

/*Basic test for setting and resetting an LED*/
void car_sw_test(){

	//Initialize some LEDs which should not be changed by setting/resetting
	shiftOut24(L1_Red + L2_Red + L4_Green + P2_Blue);
	for(;;){
		if(TL1_Car_Flag == 1){
			resetLeds(P1_Red);
		}
		if(TL1_Car_Flag == 0){
			setLeds(P1_Red);
		}
		HAL_Delay(100);
	}
}

/*Tests all LEDs and the light-variables*/
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

/*Tests the flags for the switches and buttons.*/
void flag_tester(){
	if(TL1_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L1_Green);
		//		TL1_Car_Flag = 0;
	}

	if(TL2_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L2_Green);
		//		TL2_Car_Flag = 0;
	}

	if(TL3_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L3_Green);
		//		TL3_Car_Flag = 0;
	}

	if(TL4_Car_Flag == 1){
		for(int i = 0; i<10; i++)
			blink_led(L4_Green);
		//		TL4_Car_Flag = 0;
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

/*Tests the different on/off functions as well as the transition function*/
void traffic_sequence(){
	/*Initialization*/
	trafficOnNS();
	trafficOffEW();
	pedestrianOnNS();
	pedestrianOffEW();

	/*Forever switch between NS/EW including pedestrian lights.*/
	for(;;){
		pedestrianOffNS();
		pedestrianOffEW();
		trafficTransition();
		trafficOffNS();
		trafficOnEW();
		pedestrianOnEW();

		HAL_Delay(greenDelay);

		pedestrianOffNS();
		pedestrianOffEW();
		trafficTransition();
		trafficOffEW();
		trafficOnNS();
		pedestrianOnNS();

		HAL_Delay(greenDelay);
	}
}
/*Tests the blink_led-function as well the logic of the if-statements*/
void pedestrian_test(){
	for(;;){
		if(PL2_Switch_Flag && !EWPedestrianFlag){
			pedestrian_blink_led(P2_Blue,pedestrianDelay-orangeDelay);
			pedestrianOffNS();
			pedestrianOffEW();

//			trafficTransition(); Should be here timing-wise, but in another task.

			// use these instead (*)
			resetLeds(EWTrafficRed + NSTrafficRed + EWTrafficGreen + NSTrafficGreen); //*
			setLeds(NSTrafficYellow + EWTrafficYellow); //*

			pedestrian_blink_led(P2_Blue,orangeDelay);
			trafficOffNS();
			trafficOnEW();
			pedestrianOnEW();
			PL2_Switch_Flag = 0;
			HAL_Delay(walkingDelay);
		}
		if(PL1_Switch_Flag && !NSPedestrianFlag){
			pedestrian_blink_led(P1_Blue,pedestrianDelay-orangeDelay);
			pedestrianOffNS();
			pedestrianOffEW();

			//			trafficTransition(); Should be here timing-wise, but in another task.

			// use these instead (*)
			resetLeds(EWTrafficRed + NSTrafficRed + EWTrafficGreen + NSTrafficGreen); //*
			setLeds(NSTrafficYellow + EWTrafficYellow); //*

			pedestrian_blink_led(P1_Blue,orangeDelay);
			trafficOnNS();
			trafficOffEW();
			pedestrianOnNS();

			PL1_Switch_Flag = 0;
			HAL_Delay(walkingDelay);
		}

	}
}

