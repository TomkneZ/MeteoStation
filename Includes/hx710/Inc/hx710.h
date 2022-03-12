/*
 * hx710.h
 *
 *  Created on: Jan 30, 2022
 *      Author: zaben
 */

#ifndef INCLUDES_HX710_INC_HX710_H_
#define INCLUDES_HX710_INC_HX710_H_

#include "stm32f4xx_hal.h"

typedef struct _hx710
{
	GPIO_TypeDef* gpioSck;
	GPIO_TypeDef* gpioData;
	uint16_t pinSck;
	uint16_t pinData;
	uint32_t offset;
	uint8_t gain;
	// 1: channel A, gain factor 128
	// 2: channel B, gain factor 32
    // 3: channel A, gain factor 64
} HX710;


void HX710_Init(HX710 data);
HX710 HX710_Tare(HX710 data, uint8_t times);
uint32_t HX710_Value(HX710 data);
uint32_t HX710_AverageValue(HX710 data, uint8_t times);

#endif /* INCLUDES_HX710_INC_HX710_H_ */
