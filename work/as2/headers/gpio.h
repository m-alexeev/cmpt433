#ifndef _GPIO_H_
#define _GPIO_H_

#define GPIO_PIN_LEFT_DIGIT 61
#define GPIO_PIN_RIGHT_DIGIT 44

void Gpio_write(int pin, const char* value);

#endif