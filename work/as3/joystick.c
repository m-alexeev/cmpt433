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

static void Joystick_initialize(void);



static void* Joystick_main(){
    //Export All pins 
    Joystick_initialize();
    while(notDone){

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
    Gpio_export(JOYSTICK_LEFT);
    Gpio_export(JOYSTICK_RIGHT);
    Gpio_export(JOYSTICK_DOWN);
    Gpio_export(JOYSTICK_UP);
    Gpio_export(JOYSTICK_PRESS);

    //Sleep for 300 ms before writing 
    Util_sleepForSeconds(0, 3E8);

    Gpio_write(JOYSTICK_LEFT, DIRECTION_OUT);
    Gpio_write(JOYSTICK_RIGHT, DIRECTION_OUT);
    Gpio_write(JOYSTICK_UP, DIRECTION_OUT);
    Gpio_write(JOYSTICK_DOWN, DIRECTION_OUT);
    Gpio_write(JOYSTICK_PRESS, DIRECTION_OUT);
}
