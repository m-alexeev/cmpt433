#include <stdio.h>
#include <stdlib.h>

#include "headers/gpio.h"
#include "headers/joystick.h"
#include "headers/shutdown.h"

int main(){

    Joystick_start();

    Shutdown_wait();

    Joystick_stop();
}