/*
 * functions.c
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */
#include <variables.h>
#include "gpio.h"
#include "spi.h"

uint32_t currentData = 0;

	void shiftOutbyte(uint8_t data){
	    HAL_SPI_Transmit(&hspi3, &data, 1, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_RESET);

		currentData = data;
	}

	void shiftOut24(uint32_t data){
		uint8_t data1 = data & 0xFF;
		uint8_t data2 = (data & (0xFF00)) >> 8;
		uint8_t data3 = (data & (0xFF0000)) >> 16;

//		uint8_t data3 = data & (0xFF0000);

	    HAL_SPI_Transmit(&hspi3, &data3, 1, HAL_MAX_DELAY);
	    HAL_SPI_Transmit(&hspi3, &data2, 1, HAL_MAX_DELAY);
	    HAL_SPI_Transmit(&hspi3, &data1, 1, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(_595_STCP_GPIO_Port, _595_STCP_Pin, GPIO_PIN_RESET);

		currentData = data;

	}


	void traffic_init(){
		shiftOut24(P2_Red + L2_Green + L4_Green);
	}

	void setLeds(uint32_t leds){
		currentData = currentData | (leds);
		shiftOut24(currentData);
	}
	void resetLeds(uint32_t leds){
		currentData = (~leds) & currentData;
		shiftOut24(currentData);
	}

	void blink_led(uint32_t leds){
		setLeds(leds);
		HAL_Delay(toggleFreq);
		resetLeds(leds);
		HAL_Delay(toggleFreq);
	}
