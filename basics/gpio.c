#include "headers/gpio.h"

#define EXPORT "/sys/class/gpio/export"

void echo(int data) {
    FILE *pFile = fopen(EXPORT, "w"); 
    if (pFile == NULL){
        printf("ERROR: Unable to open export file.\n"); 
        exit(1);
    }

    fprintf(pFile, "%d", data);
    fclose(pFile);
}