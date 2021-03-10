#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h> 

#include "headers/controller.h"
#include "headers/util.h"


static bool notDone = true;
static pthread_t  tid; 

static int BPM = 120;


static void* Controller_main(){

    while(notDone){
        //get Input , 
        //Queue Tracks 

        float halfBeat = (60.0 / BPM / 2);
        printf("%0.2f Beat\n", halfBeat);
        Util_sleepForSeconds(0, halfBeat * 1E9);
    }

    pthread_exit(0);
}



void Controller_start(void){
 pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Controller_main, NULL);
    if (error != 0){
        printf("Controller thread failed creation %s\n", strerror(error));
    }else{
        printf("Controller thread created successfully\n");
    }
}

void Controller_stop(void){
    pthread_join(tid, NULL);
}

void Controller_setBPM(int bpm){
    BPM = bpm;
}


int Controller_getBPM(void){
    return BPM;
}

