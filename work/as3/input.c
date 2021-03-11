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
#include "headers/controller.h"
#include "headers/mixer.h"

static pthread_t  tid; 
static bool notDone = true;

#define REG_X_MSB 0x01 
#define REG_X_LSB 0x02
#define REG_Y_MSB 0x03
#define REG_Y_LSB 0x04
#define REG_Z_MSB 0x05
#define REG_Z_LSB 0x06

#define NUM_REGISTERS 7

#define XY_THRES 0.5
#define Z_THRES 0.2

static void getAccelerometerReadings(int i2cFileDesc, float arr[]);
static void sendJoystickDirection(int direction);
static void parseAccelReadings(float accels[]);


#define BPM_CONTROL 5
#define VOL_CONTROL 5

#define MAX_BPM 300
#define MIN_BPM 40


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
                sendJoystickDirection(joystickDirection);
                Util_sleepForSeconds (0, DEBOUNCE_JOYSTICK);
                holding = Joystick_getDirection() == joystickDirection; 
            }

            float accels[3]; 
            // Get accelerometer Readings        
            getAccelerometerReadings(i2cFileDesc, accels);
            parseAccelReadings(accels);
            
            //Poll at 100HZ 
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


static void parseAccelReadings(float accels[]){
    bool hasAccel = false;

    if (fabs(accels[0]) > XY_THRES){
        printf("X Axis acceleration: %f\n",  fabs(accels[0]));
        Controller_addBeat(HI_HAT);
        hasAccel = true;
    }
    if (fabs(accels[1]) > XY_THRES){
        printf("Y Axis acceleration: %f\n", fabs(accels[1]));
        Controller_addBeat(SNARE);
        hasAccel = true;
    }
    if (fabs(accels[2]) < Z_THRES){
        printf("Z Axis acceleration: %f\n", fabs(accels[2]));
        Controller_addBeat(BASS);
        hasAccel = true;
    }
    if (hasAccel){
        Util_sleepForSeconds(0, DEBOUNCE_ACCEL);
    }
}

static void sendJoystickDirection(int direction){
    switch (direction)
    {
    case DIRECTION_PRESS:
        Controller_cycleBeat();
        break;
    case DIRECTION_LEFT:
        Input_lowerBPM();
        break;
    case DIRECTION_RIGHT:
        Input_raiseBPM();
        break;
    case DIRECTION_UP:
        Input_raiseVolume();
        break;
    case DIRECTION_DOWN:
        Input_lowerVolume();
        break;
    }
}


void Input_lowerBPM(){
    int bpm = Controller_getBPM();
    bpm -= BPM_CONTROL;
    bpm = bpm < MIN_BPM ? MIN_BPM : bpm;
    Controller_setBPM(bpm);
}

void Input_raiseBPM(){
    int bpm = Controller_getBPM();
    bpm += BPM_CONTROL;
    bpm = bpm > MAX_BPM ? MAX_BPM : bpm;
    Controller_setBPM(bpm);
}

void Input_lowerVolume(){
    int vol = Mixer_getVolume();
    vol -= VOL_CONTROL;
    vol = vol < 0 ? 0: vol;
    Mixer_setVolume(vol);

}

void Input_raiseVolume(){
    int vol = Mixer_getVolume();
    vol += VOL_CONTROL;
    vol = vol > MIXER_MAX_VOLUME ? MIXER_MAX_VOLUME: vol;
    Mixer_setVolume(vol);
}