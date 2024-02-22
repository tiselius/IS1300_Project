/*
 * variables.c
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */
#include "main.h"
#include "gpio.h"

/* LED NAMES */
const uint8_t L1_Red = 0b1;
const uint8_t L1_Yellow = 0b10;
const uint8_t L1_Green =  0b100;

const uint16_t L2_Red =    0b100000000;
const uint16_t L2_Yellow = 0b1000000000;
const uint16_t L2_Green =  0b10000000000;

const uint32_t L3_Red = 0b10000000000000000;
const uint32_t L3_Yellow = 0b100000000000000000;
const uint32_t L3_Green = 0b1000000000000000000;

const uint32_t L4_Red = 0b10000000000000000000;
const uint32_t L4_Yellow = 0b100000000000000000000;
const uint32_t L4_Green = 0b1000000000000000000000;

const uint8_t P1_Red   =  0b1000;
const uint8_t P1_Green =  0b10000;
const uint8_t P1_Blue =   0b100000;

const uint16_t P2_Red =   0b100000000000;
const uint16_t P2_Green = 0b1000000000000;
const uint16_t P2_Blue =  0b10000000000000;

/*Combined lights*/
const uint32_t NSTrafficGreen = L2_Green + L4_Green;
const uint32_t NSTrafficYellow = L2_Yellow + L4_Yellow;
const uint32_t NSTrafficRed = L2_Red + L4_Red;

const uint32_t EWTrafficGreen = L1_Green + L3_Green;
const uint32_t EWTrafficYellow = L1_Yellow + L3_Yellow;
const uint32_t EWTrafficRed = L1_Red + L3_Red;

/* Switch and Car FLAGS */
volatile uint8_t TL1_Car_Flag = 0;
volatile uint8_t TL2_Car_Flag = 0;
volatile uint8_t TL3_Car_Flag = 0;
volatile uint8_t TL4_Car_Flag = 0;

volatile uint8_t PL1_Switch_Flag = 0;
volatile uint8_t PL2_Switch_Flag = 0;


/*Light Flags*/
uint8_t NSTrafficFlag = 0; // = 1 --> green: = 0 --> red or yellow
uint8_t EWTrafficFlag = 0; // = 1 --> green: = 0 --> red or yellow
uint8_t NSPedestrianFlag = 0; // = 1 --> green: = 0 --> red
uint8_t EWPedestrianFlag = 0; // = 1 --> green: = 0 --> red

uint8_t NSPedTransitioning = 0; //Set to 1 when the lights are transitioning
uint8_t EWPedTransitioning = 0; //Set to 1 when the lights are transitioning
/*Both are not needed.*/

/* LIGHT DELAYS, FREQUENCIES */
uint8_t toggleFreq = 3;
uint16_t pedestrianDelay = 3000;
uint16_t walkingDelay = 4000;
uint16_t orangeDelay = 2000;
uint16_t greenDelay = 5000;
uint16_t redDelayMax = 10000;

/* Other */
uint32_t currentData = 0;


