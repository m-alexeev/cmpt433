#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./headers/gpio.h"


void Gpio_write(int pin, const char* value){

    char fileName[50];
    if (strcmp(value, "out") == 0 || strcmp(value, "in") == 0){
        sprintf(fileName, "/sys/class/gpio/gpio%d/direction", pin);
    }
    else{
        sprintf(fileName, "/sys/class/gpio/gpio%d/value", pin);
    }
    FILE *pFile = fopen(fileName, "w");

    if (pFile == NULL){
        printf("Error: could not write to GPIO\n");
        exit(1);
    }
    fprintf(pFile, "%s", value);
    fclose(pFile);

}
