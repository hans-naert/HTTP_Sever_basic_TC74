#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include <math.h>
#include "Driver_I2C.h"

#define EEPROM_I2C_ADDR				0x51
#define TEMP_I2C_ADDR    0x48            /* 7-bit I2C address                  */

/* I2C Driver */
#define _I2C_Driver_(n)  Driver_I2C##n
#define  I2C_Driver_(n) _I2C_Driver_(n)
extern ARM_DRIVER_I2C    I2C_Driver_(1);
extern ARM_DRIVER_I2C					Driver_I2C1;
static ARM_DRIVER_I2C *I2Cdrv = &Driver_I2C1;
#define ptrI2C         (&I2C_Driver_(1))

void I2C_SignalEvent(uint32_t event){
	
}

int32_t Temp_Read ( uint8_t *val) {
  uint8_t data;

  data = 0;
  ptrI2C->MasterTransmit(TEMP_I2C_ADDR, &data, 1, true);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 1) return -1;
  ptrI2C->MasterReceive (TEMP_I2C_ADDR, val, 1, false);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 1) return -1;

  return 0;
}

int32_t EEPROM_Initialize (bool pooling){
	int32_t status;
	uint8_t val;
	
	if(pooling == true){
		I2Cdrv->Initialize (NULL);
	}else{
		I2Cdrv->Initialize (NULL);
	}
	I2Cdrv->PowerControl (ARM_POWER_FULL);
	I2Cdrv->Control (ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
	I2Cdrv->Control (ARM_I2C_BUS_CLEAR,0);
}
