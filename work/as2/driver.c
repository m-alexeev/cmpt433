#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "./headers/knob.h"
#include "./headers/display.h"
#include "./headers/util.h"
#include "./headers/sorter.h"

//Threading 
static pthread_t  tid; 
static bool notDone = true;


static void* Driver_main(){
    int SEED_TIME = 1;
    while(notDone){
        //Pot
        //1. Read knob for size
        //2. Set next array size
        int reading = Knob_getVoltage0Reading();
        int arraySize = Knob_calculateArraySize(reading);
        Sorter_setArrayLength(arraySize);
        printf("Next array size: %d\n", arraySize);
        
        //Display
        //1. Get num arrays 
        long long sortedArraysStart = Sorter_getNumArraysSorted();

        //2. Sleep for 1 second 
        Util_sleepForSeconds(SEED_TIME, 0);
        //3. Get num arrays  again and calc difference
        long long sortedArraysEnd = Sorter_getNumArraysSorted();

        //4. Show size on screen
        long long arraysPerSecond = sortedArraysEnd - sortedArraysStart;

        if (arraysPerSecond > 99){
            arraysPerSecond = 99;
        }

        int leftDigit = arraysPerSecond / 10; 
        int rightDigit = arraysPerSecond % 10;

            Display_setDigit(LEFT_DIGIT,leftDigit);
        Display_setDigit(RIGHT_DIGIT, rightDigit);


    }
    pthread_exit(0);
}


//Start driver thread
void Driver_start(){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Driver_main, NULL);
    if (error != 0){
        printf("Driver thread failed creation %s\n", strerror(error));
    }else{
        printf("Driver thread created successfully\n");
    }
}

//Stop driver thread
void Driver_stop(){
    notDone = false;
    
    printf("Exiting driver thread\n");
    pthread_join(tid, NULL);
}