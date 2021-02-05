#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/sorter.h"
#include "./headers/util.h"

int main(int argc, char* argv[]){
    
    int size = 20; 
    Sorter_setArrayLength(size);
    
    printf("Start\n");
    Sorter_start(); 
    Sorter_start(); 

    printf("Done!\n");

}