#include <stdio.h>
#include <stdlib.h>

#include "headers/gpio.h"
#include "headers/input.h"
#include "headers/shutdown.h"

int main(){

    Input_start();

    Shutdown_wait();

    Input_stop();
}