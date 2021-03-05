#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#include "headers/joystick.h"
#include "headers/input.h"
#include "headers/gpio.h"
#include "headers/util.h"
#include "headers/i2c.h"

static pthread_t  tid; 
static bool notDone = true;

#define REG_X_1 0x01 
#define REG_X_2 0x00

static void* Input_main(){    
    //Export All pins and set direction to read
    Joystick_initialize();
    
    //Get I2c file descriptor and set the Accelerator mode to active  
    int i2cFileDesc =  I2C_initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS_ACCEL);

    I2C_writeI2cReg(i2cFileDesc, REG_ACCEL_ACT, 0x01);


    while(notDone){

        unsigned char regA = I2C_readI2cReg(i2cFileDesc, 0x0D);
        unsigned char regB = I2C_readI2cReg(i2cFileDesc, REG_X_2);

        printf("%0x%0x  \n", regA,regB);
        Util_sleepForSeconds(1,0);
        // int joystickDirection = DIRECTION_NONE;
        
        // //Wait for release
        // while(Joystick_getDirection() != DIRECTION_NONE){}
            
        // //Read joysticks for input
        // bool holding = true;
        // while (holding){
        //     joystickDirection = Joystick_getDirection();
        //     if (joystickDirection != DIRECTION_NONE){
        //         printf("Joystick direction: %d\n", joystickDirection);
        //         Util_sleepForSeconds (0, HOLD_INTERVAL);
                
        //         holding = Joystick_getDirection() == joystickDirection; 
        //     }
        // }
    }
    pthread_exit(0);
}

void Input_start(){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Input_main, NULL);
    if (error != 0){
        printf("Input thread failed creation %s\n", strerror(error));
    }else{
        printf("Input thread created successfully\n");
    }
}

void Input_stop(){
    pthread_join(tid,NULL);
}

