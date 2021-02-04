#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "./headers/sorter.h"

static int ARRAY_SIZE = 100; 
static int* ARRAY; 


//Swapper function to swap array elems
static void swapElements(int* a, int* b){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
    return;
}

//Initializes array, fills up the indexes 
static void createArray(void){
    ARRAY = (int*) malloc(ARRAY_SIZE * sizeof(int));
    if (ARRAY == NULL){
        printf("Array could not be created\n");
        exit(1);
    }
    for (int i = 0; i < ARRAY_SIZE; i ++){
        ARRAY[i] = i;
    }
    return; 
}


//Function to permutate the array
static void permutateArray(void){
    //Note: Using a modern version of the Fisher-Yates shuffle to permutate
    //Generate random seed
    srand(time(NULL));
    //Swap around the elements in the arrays
    for (int i = ARRAY_SIZE - 1; i > 0 ; i --){
        int j = (rand() % i );
        swapElements(&ARRAY[i], &ARRAY[j]);
    }
    return; 
}

// Setter for size of array
void Sorter_setArraySize(int size){
    assert(size > 0 && size < 2100); 
    ARRAY_SIZE = size; 
    return; 
}

//Getter for size of array
int Sorter_getArraySize(void){
    return ARRAY_SIZE;
}


int* Sorter_initializeArray(int size){
    assert(size > 0 && size <= 2100);
    
    createArray();
    permutateArray();
    return ARRAY; 
}


//Bubble sort the array in place
void Sorter_sortArray(){

    for (int i = 0; i < ARRAY_SIZE - 1 ; i ++){
        for (int j = 0; j < ARRAY_SIZE - i - 1 ; j ++ ){
            if (ARRAY[j] > ARRAY[j+1]){
                swapElements(&ARRAY[j], &ARRAY[j+1]);
            }
        }
    }
    return;
}


void Sorter_freeArray(void){
    free(ARRAY); 
    return;
}

