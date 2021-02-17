#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/sorter.h"
#include "./headers/util.h"
#include "./headers/i2c.h"
#include "./headers/display.h"

int main(int argc, char* argv[]){
    
    int size = 20; 
    Sorter_setArrayLength(size);
    
    printf("Start\n");
    Sorter_start(); 
    Display_start();

    sleepSecs(1);

    int length = 0;
    int* array = Sorter_getArrayData(&length);
    for (int i = 0; i < length; i ++){
        printf("%d ",array[i]);
    }
    printf("\n");
    
    free(array);
    

    Sorter_stop();
    Display_stop(); 
    printf("Done!\n");


    //Start Nework Thread and listen to input 
}