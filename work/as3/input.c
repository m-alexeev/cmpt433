#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

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


static void getAccelerometerReadings(int i2cFileDesc, float arr[]);

static void getAccelerometerReadings(int i2cFileDesc, float arr[]){
    Accelerometer_t accelReadings; 
    char* buffer = I2C_readI2cReg(i2cFileDesc, 0x00, NUM_REGISTERS);
    
    accelReadings.x = (buffer[REG_X_MSB] << 8) | (buffer[REG_X_LSB]) ;
    accelReadings.y = (buffer[REG_Y_MSB] << 8) | (buffer[REG_Y_LSB]) ;
    accelReadings.z = (buffer[REG_Z_MSB] << 8) | (buffer[REG_Z_LSB]) ;

    accelReadings.x >>= 4;
    accelReadings.y >>= 4;
    accelReadings.z >>= 4;

    float x = (float)accelReadings.x / 1024;
    float y = (float)accelReadings.y / 1024;
    float z = (float)accelReadings.z / 1024;

    arr[0] = x;
    arr[1] = y; 
    arr[2] = z;
    
    free(buffer);

}



static void* Input_main(){    
    //Export All pins and set direction to read
    Joystick_initialize();
    
    //Get I2c file descriptor and set the Accelerator mode to active  
    int i2cFileDesc =  I2C_initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS_ACCEL);

    I2C_writeI2cReg(i2cFileDesc, CTRL_REG1, 0x01);


    while(notDone){

    
        
        bool holding = true;    
        // Read joystick / accel for input 
        while (true){

            //Check for Joystick input 
            int joystickDirection = Joystick_getDirection();            
            holding = true;
            while (joystickDirection != DIRECTION_NONE && holding){
                printf("Joystick direction: %d\n", joystickDirection);
                
                Util_sleepForSeconds (0, DEBOUNCE_JOYSTICK);
                holding = Joystick_getDirection() == joystickDirection; 
            }

            float accels[3]; 

            // Get accelerometer Readings        
            getAccelerometerReadings(i2cFileDesc, accels);


            bool hasAccel = false;

            if (fabs(accels[0]) > 0.5){
                printf("X Axis acceleration: %f\n",  fabs(accels[0]));
                hasAccel = true;
            }
            if (fabs(accels[1]) > 0.5){
                printf("Y Axis acceleration: %f\n", fabs(accels[1]));
                hasAccel = true;
            }
            if (fabs(accels[2]) < 0.2){
                printf("Z Axis acceleration: %f\n", fabs(accels[2]));
                hasAccel = true;
            }
            if (hasAccel){
                Util_sleepForSeconds(0, DEBOUNCE_ACCEL);
            }

            // printf("x:%-8.5f y:%-8.5f z:%-8.5f\n", accels[0],accels[1], accels[2]);
            Util_sleepForSeconds(0, POLL_RATE);
        }
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



