#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h> 

#include "headers/controller.h"
#include "headers/util.h"
#include "headers/mixer.h"


static bool notDone = true;
static pthread_t  tid; 



static int BPM = 120;
static int currentBeat = ROCK_BEAT;



static void noBeat(){
    //Free playback buffer
}

static void rockBeat(){
    for (int i = 0; i < 4; i ++){
        float halfBeat = (60.0 / BPM / 2);
        Util_sleepForSeconds(0, halfBeat * 1E9);
    }
}

static void customBeat(){
    //Add custom beat  
}

void Controller_addBeat(int direction){
    return;
}

static void* Controller_main(){

    while(notDone){
        //get Input , 
        //Queue Tracks 
        switch (currentBeat)
        {
        case NO_BEAT:
            noBeat();
            break;
        case ROCK_BEAT:
            rockBeat();
            break;
        case CUSTOM_BEAT:
            customBeat();
            break;
        }
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


void Controller_setBeat(int beat){
    currentBeat = (currentBeat + beat) % 3;
    printf("%d\n",currentBeat);
}

int Controller_getBeat(void){
    return currentBeat;
}

void Controller_setBPM(int bpm){
    BPM = bpm;
    printf("BPM: %d\n", BPM);
}

int Controller_getBPM(void){
    return BPM;
}

