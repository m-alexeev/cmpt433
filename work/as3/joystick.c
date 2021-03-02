#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#include "headers/joystick.h"
#include "headers/gpio.h"
#include "headers/util.h"

static pthread_t  tid; 
static bool notDone = true;
int MAX_FILENAME_LEN = 50;

static const JoystickDirInfo JOYSTICK_MAPPING[JOYSTICK_COUNT] = {
    {DIRECTION_UP, JOYSTICK_UP_PIN},
    {DIRECTION_DOWN, JOYSTICK_DOWN_PIN},
    {DIRECTION_LEFT, JOYSTICK_LEFT_PIN},
    {DIRECTION_RIGHT, JOYSTICK_RIGHT_PIN},
    {DIRECTION_PRESS, JOYSTICK_PRESS_PIN},
};


//Initialize static functions
static void Joystick_initialize(void);
static int Joystick_read(char* filename);
static bool Joystick_isPressed(int direction);

static void* Joystick_main(){
    
    
    //Export All pins and set direction to read
    Joystick_initialize();
    
    while(notDone){

            

        //Read joysticks for input
        for (int dir = DIRECTION_UP; dir <= DIRECTION_PRESS; dir ++){
            Joystick_isPressed(dir);
        }
    }
    pthread_exit(0);
}

void Joystick_start(){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Joystick_main, NULL);
    if (error != 0){
        printf("Joystick thread failed creation %s\n", strerror(error));
    }else{
        printf("Joystick thread created successfully\n");
    }
}

void Joystick_stop(){
    pthread_join(tid,NULL);
}



static void Joystick_initialize(){
    //Export All Joystick pins
    for (int dir = DIRECTION_UP; dir <= DIRECTION_PRESS; dir ++){
        Gpio_export(JOYSTICK_MAPPING[dir].pinNumber);
    }
   
    //Sleep for 300 ms before writing 
    Util_sleepForSeconds(0, 3E8);
    printf("Joysticks exported\n");
    
    //Set the direction for reading the pin
    for (int dir = DIRECTION_UP; dir <= DIRECTION_PRESS; dir ++){
        Gpio_write(JOYSTICK_MAPPING[dir].pinNumber, DIR_READING);
    }
  
}

static int Joystick_read(char* fileName){
    FILE *pFile = fopen(fileName, MODE_R);
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

static bool Joystick_isPressed(int dir){
    char fileBuffer[MAX_FILENAME_LEN];
    sprintf(fileBuffer, "%s%d/value", JOYSTICK_FILE_PREFIX, JOYSTICK_MAPPING[dir].pinNumber);
    if (Joystick_read(fileBuffer) == 0){
        return true;
    }
    return false;
}