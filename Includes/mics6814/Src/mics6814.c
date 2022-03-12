/*
 * mics6814.c
 *
 *  Created on: Dec 22, 2021
 *      Author: zaben
 */
#include "mics6814.h"

void getBaseValues(uint16_t bufferNH3[10], uint16_t bufferCO[10], uint16_t bufferNO2[10])
{
	uint16_t sumNH3 = 0;
	uint16_t sumCO = 0;
	uint16_t sumNO2 = 0;

	for (int i = 0; i < 10; ++i)
	{
		sumNH3 += bufferNH3[i];
		sumNO2 += bufferNO2[i];
		sumCO += bufferCO[i];
	}

	baseNH3 = sumNH3 / 10;
	baseNO2 = sumNO2 / 10;
	baseCO = sumCO / 10;
}

float getCurrentRatio(uint16_t currentGasResistance, uint16_t baseGasResistance)
{
	return currentGasResistance / baseGasResistance * (4095.0 - baseGasResistance) / (4095.0 - currentGasResistance);
}
