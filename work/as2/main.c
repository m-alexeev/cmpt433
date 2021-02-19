#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/sorter.h"
#include "./headers/util.h"
#include "./headers/i2c.h"
#include "./headers/network.h"
#include "./headers/shutdown.h"
#include "./headers/display.h"

int main(int argc, char* argv[]){
    
    int size = 400; 
    Sorter_setArrayLength(size);
    
    printf("Start\n");
    Sorter_start(); 
    Display_start();
    Network_start();

    Shutdown_wait();

    Network_stop();
    Display_stop(); 
    Sorter_stop();

    printf("Done!\n");

}