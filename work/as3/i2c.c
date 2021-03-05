#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int I2C_initI2cBus(char* bus, int address)
{
	//Set GPIO pins to I2C
	// system("config-pin P9_17 i2c");
	// system("config-pin P9_18 i2c");


	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(-1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("Unable to set I2C device to slave address.");
		exit(-1);
	}
	return i2cFileDesc;
}


void I2C_writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = value;
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("Unable to write i2c register");
		exit(-1);
	}
}

unsigned char I2C_readI2cReg(int i2cFileDesc, unsigned char regAddr){

	int res = write(i2cFileDesc, &regAddr,sizeof(regAddr));
	if (res != sizeof(regAddr)){
		perror("I2C: Unable to write to i2c register");
		exit(1);
	}

	char value = 0; 
	res = read(i2cFileDesc, &value, sizeof(value));

	if (res != sizeof(value)){
		perror("I2C: Unable to read from i2c register");
		exit(1);
	}
	return value;
}