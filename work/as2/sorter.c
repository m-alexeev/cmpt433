#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>

#include "./headers/sorter.h"
#include "./headers/util.h"
// static int NEXT_ARRAY_SIZE = 100;
static int CUR_ARRAY_SIZE = 100; 
static long long NUM_ARRAYS_SORTED = 0; 
static int* ARRAY; 


// Setter for size of array
void Sorter_setArrayLength(int size){
    assert(size > 0 && size < 2100); 
    CUR_ARRAY_SIZE = size; 
    return; 
}

//Getter for size of array
int Sorter_getArrayLength(void){
    return CUR_ARRAY_SIZE;
}

//Return number of arrays that have completed sorting 
long long Sorter_getNumArrays_Sorted(void){
    return NUM_ARRAYS_SORTED; 
}


// Swapper function to swap array elems
static void swapElements(int* a, int* b){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
    return;
}


//Initializes array, fills up the indexes 
static void Sorter_createArray(void){
    ARRAY = (int*) malloc(CUR_ARRAY_SIZE * sizeof(int));
    if (ARRAY == NULL){
        printf("Array could not be created\n");
        exit(1);
    }

    for (int i = 0; i < CUR_ARRAY_SIZE; i ++){
        ARRAY[i] = i;
    }

    // permutate the array
    //Note: Using a modern version of the Fisher-Yates shuffle to permutate
    //Generate random seed
    srand(time(NULL));

    for (int i = CUR_ARRAY_SIZE - 1; i > 0 ; i --){
        int j = (rand() % i );
        swapElements(&ARRAY[i], &ARRAY[j]);
    }
    
    return; 
}

//Bubble sort the array in place
static void Sorter_sortArray(){
    for (int i = 0; i < CUR_ARRAY_SIZE - 1 ; i ++){
        for (int j = 0; j < CUR_ARRAY_SIZE - i - 1 ; j ++ ){
            if (ARRAY[j] > ARRAY[j+1]){
                swapElements(&ARRAY[j], &ARRAY[j+1]);
            }
        }
    }
    sleepSecs(2);
    return;

}


//Create array, shuffle it and sort 
static void* Sorter_initAndSort(void* arg){
    Sorter_createArray();
    Sorter_sortArray();
    return NULL;
}



// static void Sorter_freeArray(void){
//     free(ARRAY); 
//     return;
// }


void Sorter_start(void){

    pthread_t tid; 
    pthread_attr_t attr; 
    pthread_attr_init(&attr); 
    
    pthread_create(&tid, &attr, Sorter_initAndSort, &CUR_ARRAY_SIZE); 
    pthread_join(tid, NULL); 

    for (int i = 0; i < CUR_ARRAY_SIZE; i++){
        printf("%d ", ARRAY[i]);
    }
    printf("DONE ARRAY\n");

}


void Sorter_stop(void){
    return;
}
