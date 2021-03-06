#ifndef _I2C_H_
#define _I2C_H_

/*
    Module for setting up and writing to I2C registers
*/ 

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

#define I2C_DEVICE_ADDRESS_DISPLAY 0x20
#define I2C_DEVICE_ADDRESS_ACCEL 0x1c

#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15

#define REG_ACCEL_ACT 0x2A



int I2C_initI2cBus(char* bus, int address);

void I2C_writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);

char* I2C_readI2cReg(int i2cFiledDesc, unsigned char regAddr, int numBytes);

#endif