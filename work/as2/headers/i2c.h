#ifndef _I2C_H_
#define _I2C_H_

int I2C_initI2cBus(char* bus, int address);
void I2C_writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);



#endif