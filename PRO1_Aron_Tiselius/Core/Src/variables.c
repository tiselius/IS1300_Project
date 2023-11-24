/*
 * variables.c
 *
 *  Created on: Nov 16, 2023
 *      Author: arontiselius
 */
#include "main.h"
#include "gpio.h"

/* LED NAMES */
uint8_t L1_Red = 0b1;
uint8_t L1_Yellow = 0b10;
uint8_t L1_Green =  0b100;


uint16_t L2_Red =    0b100000000;
uint16_t L2_Yellow = 0b1000000000;
uint16_t L2_Green =  0b10000000000;

uint32_t L3_Red = 0b10000000000000000;
uint32_t L3_Yellow = 0b100000000000000000;
uint32_t L3_Green = 0b1000000000000000000;

uint32_t L4_Red = 0b10000000000000000000;
uint32_t L4_Yellow = 0b100000000000000000000;
uint32_t L4_Green = 0b1000000000000000000000;

uint8_t P1_Red   =  0b1000;
uint8_t P1_Green =  0b10000;
uint8_t P1_Blue =   0b100000;

uint16_t P2_Red =   0b100000000000;
uint16_t P2_Green = 0b1000000000000;
uint16_t P2_Blue =  0b10000000000000;

/* FLAGS */
volatile uint8_t TL1_Car_Flag = 0;
volatile uint8_t TL2_Car_Flag = 0;
volatile uint8_t TL3_Car_Flag = 0;
volatile uint8_t TL4_Car_Flag = 0;

volatile uint8_t PL1_Switch_Flag = 0;
volatile uint8_t PL2_Switch_Flag = 0;

/* LIGHT DELAYS, FREQUENCIES */

uint8_t toggleFreq = 100;
uint8_t pedestrianDelay = 10;
uint8_t walkingDelay = 10;
uint8_t orangeDelay = 10;

/* Other */
volatile uint32_t test = 0;

