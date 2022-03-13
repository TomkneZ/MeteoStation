/*
 * sds011.c
 *
 *  Created on: Mar 12, 2022
 *      Author: zaben
 */

#include "sds011.h"

/**
 * UART settings:
 *
 * Baud Rate: 9600 Bits/s
 *
 * Word Length: 8 Bits
 *
 * Parity None
 *
 * Stop Bits 1
 *
 * Enable NVIC global interrupt!
 *
 */

const unsigned char SDS_HEADER1 = 0xAA;
const unsigned char SDS_HEADER2 = 0xC0;
const unsigned char SDS_TAIL = 0xAB;

void sdsInit(SDS* sds, const UART_HandleTypeDef* huart_sds)
{
	sds->huart_sds=(UART_HandleTypeDef *)huart_sds;
	HAL_UART_Transmit(sds->huart_sds,(uint8_t*)Sds011_WorkingMode, 19,30);
	HAL_UART_Receive_IT(sds->huart_sds, sds->data_receive, 10);
}

void sdsSleepMode(SDS* sds)
{
	HAL_UART_Transmit(sds->huart_sds, (uint8_t*)Sds011_SleepCommand,19,30);
}

void sdsWorkingMode(SDS* sds)
{
	HAL_UART_Transmit(sds->huart_sds, (uint8_t*)Sds011_WorkingMode,19,30);
}

void resetValues(SDS* sds)
{
	sds->pm_10 = 0.0;
	sds->pm_2_5 = 0.0;

	for(int i=0; i<sizeof(sds->data_receive); i++)
	{
		sds->data_receive[i] = 0;
	}
}

void sds_uart_RxCpltCallback(SDS* sds, UART_HandleTypeDef *huart)
{
	if(huart == sds->huart_sds)
	{
		if((sds->data_receive[0] == SDS_HEADER1) && (sds->data_receive[1] == SDS_HEADER2))
		{
			sds->pm_2_5 = (float)((sds->data_receive[3]<<8)| sds->data_receive[2])/10;
			sds->pm_10 = (float)((sds->data_receive[5]<<8)| sds->data_receive[4])/10;
		}

		HAL_UART_Receive_IT(sds->huart_sds, sds->data_receive, 10);
	}
}
