#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "./headers/knob.h"

//Threading 
static pthread_t  tid; 
static bool notDone = true;

//Piecewise consts
#define PIECEWISE_NUM_POINTS 10
const float A2D_READINGS[] = {0,500,1000,1500,2000,2500,3000,3500,4000,4100};
const float ARRAY_SIZES[]  = {1, 20, 60, 120, 250, 300, 500, 800, 1200,2100};

//Knob readings
#define A2D_FILE_VOLTAGE0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095


static int getVoltage0Reading(){
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE0, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }
    // Get reading
    int a2dReading = 0;
    int itemsRead = fscanf(f, "%d", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }
    // Close file
    fclose(f);
    return a2dReading;
}

static int calculateArraySize(int reading){
    int index = 0; 

    //Account for min and max values 
    if (reading <= 0){
        return ARRAY_SIZES[0];
    }
    if (reading >= 4500){
        return ARRAY_SIZES[PIECEWISE_NUM_POINTS];
    }

    //Get smallest endpoint closest to reading
    for (int i = PIECEWISE_NUM_POINTS - 1; i >= 0; i --){
        if (reading >= A2D_READINGS[i]){
            index = i; 
            break;
        }
    }

    int arraySize; 
    float percentH = (reading - A2D_READINGS[index])/(A2D_READINGS[index+1]- A2D_READINGS[index]);
    // printf("%d, %f\n",reading, A2D_READINGS[index]);
    float verticalDist = ARRAY_SIZES[index + 1] - ARRAY_SIZES[index]; 

    arraySize = floor(percentH * verticalDist) + ARRAY_SIZES[index];
    printf("%d, %f, %f, %f, %f, %d\n",reading, A2D_READINGS[index], A2D_READINGS[index+1], ARRAY_SIZES[index], ARRAY_SIZES[index+1], arraySize);

    // printf("%d\n", arraySize);
    return arraySize;
}


static void*  Knob_reading(){
    while (notDone){
        int reading = getVoltage0Reading();
        // printf("%d\n", reading);
        calculateArraySize(reading);
        // printf("%d, %d\n",reading, calculateArraySize(reading));
    }
    pthread_exit(0);
}


void Knob_start(void){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Knob_reading, NULL);
    if (error != 0){
        printf("Knob thread failed creation %s\n", strerror(error));
    }else{
        printf("Knob thread created successfully\n");
    }
}



void Knob_stop(void){
    notDone = false;
    printf("Exiting knob thread\n");

    pthread_join(tid, NULL);
}
