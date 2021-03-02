#ifndef _GPIO_H_
#define _GPIO_H_

#define MODE_W "w"
#define MODE_R "r"

#define EXPORT_FILE "/sys/class/gpio/export"

void Gpio_export(int pin);

void Gpio_write(int pin, const char* value);

#endif // !_GPIO_H
