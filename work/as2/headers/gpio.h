#ifndef _GPIO_H_
#define _GPIO_H_

/*
    Module for initializing and controling GPIO pins to turn display on / off
*/ 

#define GPIO_PIN_LEFT_DIGIT 61
#define GPIO_PIN_RIGHT_DIGIT 44


// Turn GPIO pin on / off depending on value or set the direction
void Gpio_write(int pin, const char* value);

#endif