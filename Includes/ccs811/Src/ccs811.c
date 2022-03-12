#include "ccs811.h"

// Air quality values obtained from the sensor
uint16_t tVOC = 0;
uint16_t CO2 = 0;

uint8_t errvalue=0;
uint8_t mosetting=0;
uint8_t  Mode_CCS811=0x01;

void configureCCS811(const I2C_HandleTypeDef* hi2cxc)
{
    HAL_Delay(69);

    uint8_t hwID = readRegister(CSS811_HW_ID, hi2cxc);

    //Hardware ID should be 0x81
    if (hwID != 0x81){
        while (1); //Freeze
    }

    uint8_t    lodata[1];
    lodata[0]= CSS811_APP_START;
    HAL_I2C_Master_Transmit(hi2cxc, CCS811_ADDWR, lodata, 1, 100);

    HAL_Delay(20);

    setDriveMode(Mode_CCS811, hi2cxc);

    HAL_Delay(10);
}

uint8_t readRegister(uint8_t addr, const I2C_HandleTypeDef* hi2cxc)
{
	uint8_t dt;
	HAL_I2C_Mem_Read(hi2cxc, CCS811_ADDRD, (uint8_t)addr,1, &dt, 1, 300);
	return dt;
 }

void writeRegister(uint8_t addr, uint8_t val, const I2C_HandleTypeDef* hi2cxc)
{
	HAL_I2C_Mem_Write(hi2cxc, CCS811_ADDWR, (uint8_t)addr, I2C_MEMADD_SIZE_8BIT, &val, 1,300);
	while (HAL_I2C_GetState(hi2cxc) != HAL_I2C_STATE_READY){ }
	while (HAL_I2C_IsDeviceReady(hi2cxc, CCS811_ADDRD, 10, 300) == HAL_TIMEOUT);
	while(HAL_I2C_GetState(hi2cxc) != HAL_I2C_STATE_READY){}
}

void setDriveMode(uint8_t mode, const I2C_HandleTypeDef* hi2cxc)
{
	// Only 4 modes available
	if (mode > 4) mode = 4;

	//Read what's currently there
	mosetting = readRegister(CSS811_MEAS_MODE, hi2cxc);

	//Clear DRIVE_MODE bits
	mosetting &=~(7<<4);

	//Mask in mode
	mosetting |= (mode << 4);
	writeRegister(CSS811_MEAS_MODE, mosetting, hi2cxc);
	mosetting = readRegister(CSS811_MEAS_MODE, hi2cxc);
}

bool checkForError(const I2C_HandleTypeDef* hi2cxc)
{
	errvalue=readRegister(CSS811_ERROR_ID, hi2cxc);
	errvalue = readRegister(CSS811_STATUS, hi2cxc);
	return (errvalue & 1 << 0);
}

void readAlgorithmResults(const I2C_HandleTypeDef* hi2cxc)
{
    uint8_t data_rq[4];
    uint8_t status = HAL_I2C_Mem_Read(hi2cxc, CCS811_ADDRD, (uint8_t)CSS811_ALG_RESULT_DATA,
    		I2C_MEMADD_SIZE_8BIT, data_rq, 4, 100);

    /**
      *TVOC value, in parts per billion (ppb)
      *TVOC output range is from 0 to 1187
      *eC02 value, in parts per million (ppm)
      *eC02 output range is from 400 to 8192
    */
    CO2 = ((uint16_t)data_rq[0] << 8) | ((uint16_t)data_rq[1]);
    tVOC = ((uint16_t)data_rq[2] << 8) | ((uint16_t)data_rq[3]);
}

bool DataReady(const I2C_HandleTypeDef* hi2cxc)
{
	uint8_t status = readRegister(CSS811_STATUS, hi2cxc);
	return (1 << 3) & status;
}

uint16_t getVOC()
{
	return tVOC;
}

uint16_t getCO2()
{
	return CO2;
}

void clearAlgorithmResults()
{
	tVOC = 0;
	CO2 = 0;
}
