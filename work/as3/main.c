#include <stdio.h>
#include <stdlib.h>

#include "headers/gpio.h"
#include "headers/input.h"
#include "headers/shutdown.h"
#include "headers/mixer.h"
#include "headers/controller.h"

int main(){


    Mixer_init();
    Controller_start();
    Input_start();


    Shutdown_wait();

    Input_stop();
    Controller_stop();
}