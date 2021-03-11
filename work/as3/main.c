#include <stdio.h>
#include <stdlib.h>

#include "headers/network.h"
#include "headers/gpio.h"
#include "headers/input.h"
#include "headers/shutdown.h"
#include "headers/mixer.h"
#include "headers/controller.h"

int main(){


    Mixer_init();
    Network_start();
    Controller_start();
    Input_start();


    Shutdown_wait();

    Input_stop();
    Controller_stop();
    Network_stop();
    Mixer_cleanup();

}