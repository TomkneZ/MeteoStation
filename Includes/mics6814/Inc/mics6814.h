/*
 * mics6814.h
 *
 *  Created on: Dec 22, 2021
 *      Author: zaben
 */

#ifndef INCLUDES_MICS6814_INC_MICS6814_H_
#define INCLUDES_MICS6814_INC_MICS6814_H_

#include "stm32f4xx_hal.h"

uint16_t baseNH3;
uint16_t baseCO;
uint16_t baseNO2;

void getBaseValues(uint16_t bufferNH3[10], uint16_t bufferCO[10], uint16_t bufferNO2[10]);
float getCurrentRatio(uint16_t currentGasResistance, uint16_t baseGasResistance);

#endif /* INCLUDES_MICS6814_INC_MICS6814_H_ */
