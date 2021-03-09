#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/sorter.h"
#include "./headers/util.h"
#include "./headers/network.h"
#include "./headers/shutdown.h"
#include "./headers/display.h"
#include "./headers/driver.h"

int main(int argc, char* argv[]){
    
    
    printf("Start\n");
  
    Display_start();
    Driver_start();
    Sorter_start(); 
    Network_start();

    // Wait for shutdown from network thread
    Shutdown_wait();
    
    Network_stop();
    Sorter_stop();
    Driver_stop();
    Display_stop(); 

    printf("Finished!\n");

}