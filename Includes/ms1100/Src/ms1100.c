/*
 * ms1100.c
 *
 *  Created on: Dec 3, 2021
 *      Author: zaben
 */
#include "ms1100.h"

float getFormaldehydeConcentration(float adc_value)
{
	float voltage = adc_value * (5.0 / 1023.0);
	float logTemp = (-2.631) + 1.528 * voltage + (-0.125) * voltage * voltage;

	return pow(10, logTemp);
}

float getTolueneConcentration(float adc_value)
{
	float voltage = adc_value * (5 / 1023);
	float logTemp = (-7.071) + 2.852 * voltage + (-0.210) * voltage * voltage;

	return pow(10, logTemp);
}


