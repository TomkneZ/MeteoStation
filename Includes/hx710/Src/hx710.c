/*
 * hx710.c
 *
 *  Created on: Jan 30, 2022
 *      Author: zaben
 */

#include "hx710.h"

float RES = 1.96695328e-7;

void HX710_Init(HX710 data)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = data.pinSck;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(data.gpioSck, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = data.pinData;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(data.gpioData, &GPIO_InitStruct);

	HAL_GPIO_WritePin(data.gpioSck, data.pinSck, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(data.gpioSck, data.pinSck, GPIO_PIN_RESET);
}

uint32_t HX710_Average_Value(HX710 data, uint8_t times)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < times; i++)
    {
        sum += HX710_Value(data);
    }

    return sum / times;
}

uint32_t HX710_Value(HX710 data)
{
    uint32_t buffer;
    buffer = 0;

    while (HAL_GPIO_ReadPin(data.gpioData, data.pinData)==1);

    for (uint8_t i = 0; i < 24; i++)
    {
    	HAL_GPIO_WritePin(data.gpioSck, data.pinSck, GPIO_PIN_SET);

        buffer = buffer << 1;

        if (HAL_GPIO_ReadPin(data.gpioData, data.pinData))
        {
            buffer ++;
        }

        HAL_GPIO_WritePin(data.gpioSck, data.pinSck, GPIO_PIN_RESET);
    }

    for (uint8_t i = 0; i < data.gain; i++)
    {
    	HAL_GPIO_WritePin(data.gpioSck, data.pinSck, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(data.gpioSck, data.pinSck, GPIO_PIN_RESET);
    }

    buffer = buffer ^ 0x800000;

    return buffer;
}

HX710 HX710_Tare(HX710 data, uint8_t times)
{
    uint32_t sum = HX710_Average_Value(data, times);
    data.offset = sum;
    return data;
}

float HX710_pascal(HX710 data, uint8_t times){
	double t1 = (double)HX710_Average_Value(data, times);
	double t2 = t1 * RES;
	double t3 = t2 * 200;
	double t4 = t3 + 500;

    float value = (HX710_Average_Value(data, times)*RES)*200 + 500;
    return value;
}

float HX710_atm(HX710 data, uint8_t times){
    float value = HX710_pascal(data, times)*9.86923E-6;
    return value;
}

float HX710_mmHg(HX710 data, uint8_t times){
    float value = HX710_pascal(data, times)*0.00750062;
    return value;
}

float HX710_psi(HX710 data, uint8_t times){
    float value = HX710_pascal(data, times)*0.000145038;
    return value;
}

