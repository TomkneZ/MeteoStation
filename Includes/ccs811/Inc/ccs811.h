#ifndef CCS811_H
#define CCS811_H

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define CCS811_ADDRD 0xB4 //7-bit shifted default I2C Address
#define CCS811_ADDWR 0XB4
#define CSS811_STATUS 0x00
#define CSS811_MEAS_MODE 0x01
#define CSS811_ALG_RESULT_DATA 0x02
#define CSS811_RAW_DATA 0x03
#define CSS811_ENV_DATA 0x05
#define CSS811_NTC 0x06
#define CSS811_THRESHOLDS 0x10
#define CSS811_BASELINE 0x11
#define CSS811_HW_ID 0x20
#define CSS811_HW_VERSION 0x21
#define CSS811_FW_BOOT_VERSION 0x23
#define CSS811_FW_APP_VERSION 0x24
#define CSS811_ERROR_ID 0xE0
#define CSS811_APP_START 0xF4
#define CSS811_SW_RESET 0xFF

void configureCCS811(const I2C_HandleTypeDef* hi2cxc);

uint8_t readRegister(uint8_t addr, const I2C_HandleTypeDef* hi2cxc);

uint16_t getCO2();
uint16_t getVOC();

void writeRegister(uint8_t addr, uint8_t val, const I2C_HandleTypeDef* hi2cxc);
void setDriveMode(uint8_t mode, const I2C_HandleTypeDef* hi2cxc);
void readAlgorithmResults(const I2C_HandleTypeDef* hi2cxc);
void clearAlgorithmResults();

bool checkForError(const I2C_HandleTypeDef* hi2cxc);
bool DataReady(const I2C_HandleTypeDef* hi2cxc);

#endif
