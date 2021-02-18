#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/sorter.h"
#include "./headers/util.h"
#include "./headers/i2c.h"
#include "./headers/display.h"

int main(int argc, char* argv[]){
    
    int size = 400; 
    Sorter_setArrayLength(size);
    
    printf("Start\n");
    Sorter_start(); 
    Display_start();


    //Call stop inside network module
    Sorter_stop();
    Display_stop(); 

    printf("Done!\n");

}