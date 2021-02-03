#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "./headers/arrayController.h"

// static int ARRAY_SIZE = 100; 

//Creates randomly permutated array
static int*  createArray(int size){
    //TODO Create Array of set size
    int* arr = (int*) malloc(size * sizeof(int));
    if (arr == NULL){
        printf("Array could not be created\n");
        exit(1);
    }

    for (int i = 0; i < size; i ++){
        arr[i] = i;
    }
    return arr; 
}

static int* permutateArray(int *arr, int size){
    //Using a modern version of the Fisher-Yates shuffle
   
    //Generate random seed
    srand(time(NULL));
    //Swap around the elements in the arrays
    for (int i = size - 1; i > 0 ; i --){
        int j = (rand() % i ); 
        int temp = arr[i]; 
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return arr;
}


// void setArraySize(int size){
//     return;
// }

// int getArraySize(void){
//     return 0 ;
// }


int* initializeArray(int size){
    assert(size > 0 && size <= 2100);
    int* arr = createArray(size);
    for (int i = 0; i< size; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    arr = permutateArray(arr, size);
    for (int i = 0; i< size; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return arr; 
}




void sortArray(){
    return;
}


void freeArray(int* arr){
    free(arr); 
    return;
}

