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


static void swapElements(int* a, int* b){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}


static int* permutateArray(int *arr, int size){
    //Using a modern version of the Fisher-Yates shuffle
   
    //Generate random seed
    srand(time(NULL));
    //Swap around the elements in the arrays
    for (int i = size - 1; i > 0 ; i --){
        int j = (rand() % i );
        swapElements(&arr[i], &arr[j]);
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
    arr = permutateArray(arr, size);
    return arr; 
}




int* sortArray(int* arr, int size){

    for (int i = 0; i < size - 1 ; i ++){
        for (int j = 0; j < size - i - 1 ; j ++ ){
            if (arr[j] > arr[j+1]){
                swapElements(&arr[j], &arr[j+1]);
            }
        }
    }
    return arr; 
}


void freeArray(int* arr){
    free(arr); 
    return;
}

