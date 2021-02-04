#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/sorter.h"

int main(int argc, char* argv[]){
    
    int size = 10; 
    Sorter_setArraySize(size);
    int* arr = Sorter_initializeArray(size);
    
    for (int i = 0; i < size; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");
        

    Sorter_sortArray();

    for (int i = 0; i < size; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");


    Sorter_freeArray();

}