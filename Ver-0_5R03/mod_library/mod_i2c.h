
#ifndef MOD_I2C_H_
#define MOD_I2C_H_


#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_usci_xx.h"


#define I2C_MultiMaster     UCMM
#define I2C_SingleMaster    0
#define I2C_MasterAddr10Bit UCA10
#define I2C_MasterAddr7Bit  0
#define I2C_SlaveAddr10Bit  UCSLA10
#define I2C_SlaveAddr7Bit   0
#define I2C_SlaveMode       0
#define I2C_MasterMode      UCMST




void i2cUCB0Init(uint8_t regConf, uint8_t clkDiv,uint8_t addressOwn);
uint8_t i2cUCB0Write(uint8_t varIn);
void i2cUCB0StartWrite(uint8_t slaveAddress);
uint8_t i2cUCB0Read(void);
void i2cUCB0StartRead(uint8_t slaveAddress);
void i2cUCB0Stop(void);
void i2cUCB0StopEnd(void);


#endif /* MOD_I2C_H_ */
