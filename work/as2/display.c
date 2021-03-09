#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "./headers/display.h"
#include "./headers/i2c.h"
#include "./headers/util.h"
#include "./headers/gpio.h"


#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"


static const Digit digits[10] = {
	{0x86, 0xA1},  	//0
	{0x12, 0x80}, 	//1
	{0x0E, 0x31},	//2
	{0x06, 0x80},	//3
	{0x8A, 0x90},	//4
	{0x8C, 0xB0},	//5
	{0x8C, 0xB1}, 	//6
	{0x14, 0x04},	//7
	{0x8E, 0xB1},	//8
	{0x8E, 0x90}	//9
};


static pthread_t  tid; 
static bool notDone = true;

static Digit displayDigits[2] = {{0x86, 0xA1}, {0x86, 0xA1}};



void Display_setDigit(int digit, int value){
	displayDigits[digit] = digits[value]; 
}

Digit Display_getDigit(int digit){
	return displayDigits[digit];
}


static void* Display_main(){
	
	//Set up i2c for writing
	int i2cFileDesc = I2C_initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);


	I2C_writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
	I2C_writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

	Digit curDigit = displayDigits[0];

	Gpio_write(GPIO_PIN_LEFT_DIGIT, GPIO_OUT);
	Gpio_write(GPIO_PIN_RIGHT_DIGIT, GPIO_OUT);

	//Thread Loop
	while(notDone){
		Gpio_write(GPIO_PIN_RIGHT_DIGIT, DIGIT_OFF);
		Gpio_write(GPIO_PIN_LEFT_DIGIT, DIGIT_OFF);

		curDigit = Display_getDigit(RIGHT_DIGIT);
		I2C_writeI2cReg(i2cFileDesc, REG_OUTB, curDigit.topBits);
		I2C_writeI2cReg(i2cFileDesc, REG_OUTA, curDigit.botBits);
		Gpio_write(GPIO_PIN_RIGHT_DIGIT, DIGIT_ON);

		Util_sleepForSeconds(0,DISPLAY_DELAY);

		Gpio_write(GPIO_PIN_RIGHT_DIGIT, DIGIT_OFF);
		Gpio_write(GPIO_PIN_LEFT_DIGIT, DIGIT_OFF);
		
		curDigit = Display_getDigit(LEFT_DIGIT);
		I2C_writeI2cReg(i2cFileDesc, REG_OUTB, curDigit.topBits);
		I2C_writeI2cReg(i2cFileDesc, REG_OUTA, curDigit.botBits);
		Gpio_write(GPIO_PIN_LEFT_DIGIT, DIGIT_ON);

		Util_sleepForSeconds(0,DISPLAY_DELAY);

	}
	
	//Turn off display before exiting
	Gpio_write(GPIO_PIN_RIGHT_DIGIT, DIGIT_OFF);
	Gpio_write(GPIO_PIN_LEFT_DIGIT, DIGIT_OFF);


	pthread_exit(0);
}


void Display_start(){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Display_main, NULL);
    if (error != 0){
        printf("Display thread failed creation %s\n", strerror(error));
    }else{
        printf("Display thread created successfully\n");
    }
}


void Display_stop(){
	notDone = false;

	printf("Exiting Display Thread\n");
	pthread_join(tid,NULL);
}