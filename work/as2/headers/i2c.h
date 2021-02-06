#ifndef _I2C_H_
#define _I2C_H_

int initI2cBus(char* bus, int address);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);



#endif