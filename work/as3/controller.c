#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h> 

#include "headers/controller.h"
#include "headers/util.h"
#include "headers/mixer.h"
#include "headers/input.h"

static bool notDone = true;
static pthread_t  tid; 

static int BPM = 120;
static int currentBeat = ROCK_BEAT;

static wavedata_t beatArr[5]; 


static void initializeBeatArray();



static void noBeat(){
    //Free playback buffer
    Mixer_freeQueue();
}

static void rockBeat(){
    for (int i = 0; i < 4; i ++){
        float halfBeat = (60.0 / BPM / 2);
        Mixer_queueSound(&beatArr[HI_HAT]);
        if(i == 0){
            Mixer_queueSound(&beatArr[BASS]);
        }if (i==2){
            Mixer_queueSound(&beatArr[SNARE]);
        }
        Util_sleepForSeconds(0, halfBeat * 1E9);
    }
}

static void customBeat(){
    //Add custom beat  
    for (int i = 0; i < 4; i++){
        Mixer_queueSound(&beatArr[SNARE]);
        Mixer_queueSound(&beatArr[HI_HAT]);
        if (i % 2 == 0){
            Mixer_queueSound(&beatArr[BASS]);
        }
        float halfBeat = (60.0 / BPM / 2);
        Util_sleepForSeconds(0, halfBeat * 1E9);
    }
}

void Controller_addBeat(int direction){
    Mixer_queueSound(&beatArr[direction]);
}

static void* Controller_main(){

    initializeBeatArray();
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


void Controller_cycleBeat(){
    currentBeat = (currentBeat + 1) % 3;
    printf("Current Beat: %d\n",currentBeat);
}

void Controller_setBeat(int beat){
    currentBeat = beat;
    printf("Current Beat: %d\n",currentBeat);
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

static void initializeBeatArray(){
    Mixer_readWaveFileIntoMemory(SOURCE_BDRUM, &beatArr[BASS]);
    Mixer_readWaveFileIntoMemory(SOURCE_HIHAT, &beatArr[HI_HAT]);
    Mixer_readWaveFileIntoMemory(SOURCE_SNARE, &beatArr[SNARE]);
}