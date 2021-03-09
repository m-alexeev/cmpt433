#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>

#include "headers/joystick.h"
#include "headers/gpio.h"
#include "headers/util.h"
int MAX_FILENAME_LEN = 80;

static const JoystickDirInfo JOYSTICK_MAPPING[NUM_DIRECTIONS] = {
    {DIRECTION_UP, JOYSTICK_UP_PIN},
    {DIRECTION_DOWN, JOYSTICK_DOWN_PIN},
    {DIRECTION_LEFT, JOYSTICK_LEFT_PIN},
    {DIRECTION_RIGHT, JOYSTICK_RIGHT_PIN},
    {DIRECTION_PRESS, JOYSTICK_PRESS_PIN},
};

void Joystick_initialize(){
    //Export All Joystick pins
    for (int dir = DIRECTION_UP; dir <= DIRECTION_PRESS; dir ++){
        Gpio_export(JOYSTICK_MAPPING[dir].pinNumber);
    }
   
    //Sleep for 400 ms before writing 
    Util_sleepForSeconds(0, 4E8);
    printf("Joysticks exported\n");
    
    //Set the direction for reading the pin
    for (int dir = DIRECTION_UP; dir <= DIRECTION_PRESS; dir ++){
        Gpio_write(JOYSTICK_MAPPING[dir].pinNumber, DIR_READING);
    }
  
}



int Joystick_read(char* fileName){
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL){
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }

    const int MAX_LENGTH = 1024; 
    char buff[MAX_LENGTH];
    fgets(buff, MAX_LENGTH, pFile);

    fclose(pFile);
    int joystickDirection = atoi(buff);
    return joystickDirection;
}

int Joystick_getDirection(){
    char fileBuffer[MAX_FILENAME_LEN];

    for (int dir = DIRECTION_UP; dir < NUM_DIRECTIONS; dir ++){
        memset(fileBuffer, 0, MAX_FILENAME_LEN);
        
        sprintf(fileBuffer, "%s%d/value", JOYSTICK_FILE_PREFIX, JOYSTICK_MAPPING[dir].pinNumber);
        if (Joystick_read(fileBuffer) == 0){
            return dir;
        }
    }
    return DIRECTION_NONE;
}