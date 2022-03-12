/*
 * sds011.h
 *
 *  Created on: Mar 12, 2022
 *      Author: zaben
 */

#ifndef INCLUDES_SDS011_INC_SDS011_H_
#define INCLUDES_SDS011_INC_SDS011_H_

#include "stm32f4xx_hal.h"

typedef struct SDS_t {
  UART_HandleTypeDef* huart_sds;
  uint16_t pm_2_5;
  uint16_t  pm_10;
  uint8_t data_receive[19];
} SDS;


static const uint8_t Sds011_SleepCommand[] = {
		0xAA,
		0xB4,
		0x06,
		0x01,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0xFF,
		0xFF,
		0x05,
		0xAB
};

static const uint8_t Sds011_WorkingMode[] = {
		0xAA,
		0xB4,
		0x06,
		0x01,
		0x01,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0xFF,
		0xFF,
		0x06,
		0xAB
};
void resetValues(SDS* sds);

void sdsInit(SDS* sds, const UART_HandleTypeDef* huart_sds);
void sds_uart_RxCpltCallback(SDS* sds, UART_HandleTypeDef *huart);

void sdsWorkingMode(SDS* sds);
void sdsSleepMode(SDS* sds);

#endif /* INCLUDES_SDS011_INC_SDS011_H_ */
