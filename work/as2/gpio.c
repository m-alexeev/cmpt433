#include <stdlib.h>
#include <stdio.h>

#include "./headers/gpio.h"


void Gpio_write(int pin, const char* value){
    char fileName[50];
    sprintf(fileName, "/sys/class/gpio/gpio%d/value", pin);
    FILE *pFile = fopen(fileName, "w");

    if (pFile == NULL){
        printf("Error: could not write to GPIO\n");
        exit(1);
    }
    fprintf(pFile, "%s", value);
    fclose(pFile);

}
