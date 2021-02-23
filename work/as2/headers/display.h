#ifndef _DISPLAY_H
#define _DISPLAY_H_

//Module for controlling the I2C display
#define I2C_DEVICE_ADDRESS 0x20

#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15

#define DIGIT_OFF "0"
#define DIGIT_ON  "1" 

#define DISPLAY_DELAY 5E6 


typedef struct Digit{	
	int topBits;
	int botBits;
}Digit;

#define LEFT_DIGIT 0
#define RIGHT_DIGIT 1

//Starts I2C display thread
void Display_start(void);


//Stops I2C display thread
void Display_stop(void);


void Display_setDigit(int DIGIT, int value);

Digit Display_getDigit(int DIGIT);
	



#endif