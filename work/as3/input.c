#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#include "headers/joystick.h"
#include "headers/input.h"
#include "headers/gpio.h"
#include "headers/util.h"
#include "headers/i2c.h"

static pthread_t  tid; 
static bool notDone = true;

#define REG_X_MSB 0x01 
#define REG_X_LSB 0x02
#define REG_Y_MSB 0x03
#define REG_Y_LSB 0x04
#define REG_Z_MSB 0x05
#define REG_Z_LSB 0x06

#define NUM_REGISTERS 7

static void* Input_main(){    
    //Export All pins and set direction to read
    Joystick_initialize();
    
    //Get I2c file descriptor and set the Accelerator mode to active  
    int i2cFileDesc =  I2C_initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS_ACCEL);

    I2C_writeI2cReg(i2cFileDesc, REG_ACCEL_ACT, 0x01);


    while(notDone){

        
        char* buffer = I2C_readI2cReg(i2cFileDesc, 0x00, NUM_REGISTERS);

        Accelerometer_t accelReadings; 
        accelReadings.x = (buffer[REG_X_MSB] << 8) | (buffer[REG_X_LSB]);
        accelReadings.y = (buffer[REG_Y_MSB] << 8) | (buffer[REG_Y_LSB]);
        accelReadings.z = (buffer[REG_Z_MSB] << 8) | (buffer[REG_Z_LSB]);

        printf("x:%-8d y:%-8d z:%-8d\n", accelReadings.x, accelReadings.y, accelReadings.z);

        Util_sleepForSeconds(0, 5E5);
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
        free(buffer);
    }
    //Exit thread
    close (i2cFileDesc);
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

