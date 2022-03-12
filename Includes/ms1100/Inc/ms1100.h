/*
 * ms1100.h
 *
 *  Created on: Dec 3, 2021
 *      Author: zaben
 */

#ifndef INC_MS1100_H_
#define INC_MS1100_H_

#include "stm32f4xx_hal.h"

float getFormaldehydeConcentration(float adc_value);
float getTolueneConcentration(float adc_value);

#endif /* INC_MS1100_H_ */
