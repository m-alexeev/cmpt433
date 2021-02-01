#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#include "headers/joystick.h"
#include "headers/utils.h"

static const char joystickFile[] = "/sys/class/gpio/gpio";

// check if the direction is valid 
static void assertDirection(eJoystickDirections direction); 

struct DirectionInfo{
    const char* name;
    const int pinNumber;
};

const struct DirectionInfo directions[] ={
    {"Up",      26},
    {"Down",    46},
    {"Left",    65},
    {"Right",   47}, 
    {"Center",  27},
};


bool Joystick_isPressed(){
    for (int i = JOYSTICK_DOWN; i < JOYSTICK_MAX_DIRECTIONS; i++){
        Joystick_isDirectionPressed(i);
    }
    return false; 
}

bool Joystick_isDirectionPressed(eJoystickDirections direction){
    assertDirection(direction);
    char filename[50]; 

    sprintf(filename, "%s%d/value",joystickFile, directions[direction].pinNumber);
    if (atoi(readFromFile(filename)) == 0){
        return true;
    }


    return false;
}

static void assertDirection(eJoystickDirections dir){
    assert(dir >= 0 && dir < JOYSTICK_MAX_DIRECTIONS);
}




