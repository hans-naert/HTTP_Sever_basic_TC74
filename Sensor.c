#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include <math.h>
#include "Driver_I2C.h"
#include "Sensor.h"

#define TEMP_I2C_ADDR    0x48            /* 7-bit I2C address                  */

/* I2C driver instance */
extern ARM_DRIVER_I2C            Driver_I2C1;
static ARM_DRIVER_I2C *I2Cdrv = &Driver_I2C1;

void I2C_SignalEvent(uint32_t event){
	
}

uint8_t TC74_read () {
  uint8_t data;
	uint8_t val;

  data = 0;
  I2Cdrv->MasterTransmit(TEMP_I2C_ADDR, &data, 1, true);
  while (I2Cdrv->GetStatus().busy);
  if (I2Cdrv->GetDataCount() != 1) return -1;
  I2Cdrv->MasterReceive (TEMP_I2C_ADDR, &val, 1, false);
  while (I2Cdrv->GetStatus().busy);
  if (I2Cdrv->GetDataCount() != 1) return -1;

  return val;
}

void TC74_Initialize (){
	int32_t status;

  I2Cdrv->Initialize (NULL);

	I2Cdrv->PowerControl (ARM_POWER_FULL);
	I2Cdrv->Control (ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);
	I2Cdrv->Control (ARM_I2C_BUS_CLEAR,0);
}
