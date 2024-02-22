/**
******************************************************************************
@brief Functions used in traffic light project.
@file functions.c
@author Aron Tiselius
@version 1.0
@date 19-dec-2023
******************************************************************************
*/


#include <variables.h>
#include "gpio.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/**
@brief shiftOutbyte, sends one byte of data to shift registers and clocks the latch. Updates the global variable currentData.
@param uint8_t data, the data which is sent to the shift registers.
@return void
*/
void shiftOutbyte(uint8_t data){
	HAL_SPI_Transmit(&hspi3, &data, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_RESET);

	currentData = data;
}

/**
@brief shiftOut24, sends 3 bytes of data to shift registers and clocks the latch. Updates the global variable currentData.
@param uint32_t data, the data which is sent to the shift registers.
@return void
*/
void shiftOut24(uint32_t data){
	uint8_t data1 = data & 0xFF;
	uint8_t data2 = (data & (0xFF00)) >> 8;
	uint8_t data3 = (data & (0xFF0000)) >> 16;

	HAL_SPI_Transmit(&hspi3, &data3, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi3, &data2, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi3, &data1, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_RESET);

	currentData = data;
	osDelay(1);
}

/*NOT USED?*/
void traffic_init(){
	shiftOut24(P2_Red + L2_Green + L4_Green);
}

/**
@brief setLeds, turns on the LED(s) specified in the input. Does not affect other LEDs.
@param uint32_t leds, the data which is updated/changed from the currentData.
@return void
*/
void setLeds(uint32_t leds){
	currentData = currentData | (leds);
	shiftOut24(currentData);
}

/**
@brief resetLeds, turns off the LED(s) specified in the input. Does not affect other LEDs.
@param uint32_t leds, the data which is updated/changed from the currentData.
@return void
*/
void resetLeds(uint32_t leds){
	currentData = (~leds) & currentData;
	shiftOut24(currentData);
}

/**
@brief blink_led, "blinks" the LED(s) which are specified in the input once. A delay of 250ms between setting and resetting.
 	   Used for testing LEDs, not used in the final project.
@param uint32_t leds, the leds which will blink.
@return void
*/
void blink_led(uint32_t leds){
	setLeds(leds);
	HAL_Delay(250);
	resetLeds(leds);
	HAL_Delay(250);
}

/**
@brief pedestrian_blink_led, blinks the specified LED(s) for a specified amount of time. Blinks with a frequency of toggleFreq.
@param1 uint32_t leds, the data which is updated/changed from the currentData.
@param2	uint32_t time, the time which the LED(s) blink.
@return void
*/
void pedestrian_blink_led(uint32_t leds,uint32_t time){
	const TickType_t blinkPeriod = pdMS_TO_TICKS(1000 / toggleFreq); // Convert frequency to period.

	for (TickType_t elapsedTicks = 0; elapsedTicks < pdMS_TO_TICKS(time); elapsedTicks += blinkPeriod) {
		setLeds(leds);
		vTaskDelay(blinkPeriod/2);
		resetLeds(leds);
		vTaskDelay(blinkPeriod/2);
	}
}

/**
@brief trafficOnNS, turns off both north and south yellow lights, turn on both north and south green lights and sets NSTrafficFlag to 1.
@return void
*/
void trafficOnNS(){
	resetLeds(NSTrafficYellow);
	setLeds(NSTrafficGreen);
	NSTrafficFlag = 1;
}

/**
@brief trafficOffNS, turns off both north and south yellow lights, turn on both north and south red lights and sets NSTrafficFlag to 0.
@return void
*/
void trafficOffNS(){
	resetLeds(NSTrafficYellow);
	setLeds(NSTrafficRed);
	NSTrafficFlag = 0;
}

/**
@brief trafficOnEW, turns off both east and west yellow lights, turn on both east and west green lights and sets EWTrafficFlag to 1.
@return void
*/
void trafficOnEW(){
	resetLeds(EWTrafficYellow);
	setLeds(EWTrafficGreen);
	EWTrafficFlag = 1;
}

/**
@brief trafficOffEW, turns off both east and west yellow lights, turn on both east and west red lights and sets EWTrafficFlag to 0.
@return void
*/
void trafficOffEW(){
	resetLeds(EWTrafficYellow);
	setLeds(EWTrafficRed);
	EWTrafficFlag = 0;
}
/**
@brief trafficTransition, acts as the transition between light changes.
	   Turns off all red and green traffic lights, turns on both yellow traffic lights for orangeDelay ms.
	   Sets EWTrafficFlag and NSTrafficFlag to 0.
@return void
*/
void trafficTransition(){
	NSPedTransitioning = 1;
	EWPedTransitioning = 1;

	resetLeds(EWTrafficRed);
	resetLeds(NSTrafficRed);
	resetLeds(EWTrafficGreen);
	resetLeds(NSTrafficGreen);
	setLeds(NSTrafficYellow + EWTrafficYellow);
	EWTrafficFlag = 0;
	NSTrafficFlag = 0;
	vTaskDelay(pdMS_TO_TICKS(orangeDelay));
	NSPedTransitioning = 0;
	EWPedTransitioning = 0;
}

/**
@brief pedestrianOnNS, sets the NS pedestrian light to green, turns off the red NS pedestrian light. Sets NSPedestrianFlag to 1.
@return void
*/
void pedestrianOnNS(){
	setLeds(P1_Green);
	resetLeds(P1_Red);
	NSPedestrianFlag = 1;
	NSPedTransitioning = 0;
	EWPedTransitioning = 0;
}

/**
@brief pedestrianOffNS, sets the NS pedestrian light to red, turns off the green NS pedestrian light. Sets NSPedestrianFlag to 0.
@return void
*/
void pedestrianOffNS(){
	resetLeds(P1_Green);
	setLeds(P1_Red);
	NSPedestrianFlag = 0;
	NSPedTransitioning = 0;
	EWPedTransitioning = 0;
}

/**
@brief pedestrianOnEW, sets the EW pedestrian light to green, turns off the red EW pedestrian light. Sets EWPedestrianFlag to 1.
@return void
*/
void pedestrianOnEW(){
	setLeds(P2_Green);
	resetLeds(P2_Red);
	EWPedestrianFlag = 1;
	EWPedTransitioning = 0;
	NSPedTransitioning = 0;
}

/**
@brief pedestrianOffEW, sets the EW pedestrian light to red, turns off the green EW pedestrian light. Sets EWPedestrianFlag to 0.
@return void
*/
void pedestrianOffEW(){
	resetLeds(P2_Green);
	setLeds(P2_Red);
	EWPedestrianFlag = 0;
	EWPedTransitioning = 0;
	NSPedTransitioning = 0;
}




