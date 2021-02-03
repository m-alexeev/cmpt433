#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/arrayController.h"

int main(int argc, char* argv[]){
    
    int size = 10; 
    
    int* arr = initializeArray(size);
    
    for (int i = 0; i < size; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");
        

    arr = sortArray(arr, size); 
    for (int i = 0; i < size; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");


    freeArray(arr);

}