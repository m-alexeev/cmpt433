#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "./headers/sorter.h"
#include "./headers/util.h"


//Defining module variables 

static int NEXT_ARRAY_SIZE = 100;
static int CUR_ARRAY_SIZE = 100;
static long long NUM_ARRAYS_SORTED = 0; 
static int* ARRAY; 

//Threading
static pthread_t tid;
pthread_mutex_t array_mutex = PTHREAD_MUTEX_INITIALIZER;  
static bool notDone = true;


// ==== LOCAL FUNCTIONS ==== //


// Swapper function to swap array elems
static void swapElements(int* a, int* b){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
    return;
}


//Initializes array, fills up the indexes 
static void Sorter_createArray(void){   
    pthread_mutex_lock(&array_mutex);{
        ARRAY = (int*) malloc(CUR_ARRAY_SIZE * sizeof(int));
        memset(ARRAY, 0, CUR_ARRAY_SIZE * sizeof(int));
        if (ARRAY == NULL){
            printf("Array could not be created\n");
            exit(1);
        }
        for (int i = 0; i < CUR_ARRAY_SIZE; i ++){
            ARRAY[i] = i;
        }
    }pthread_mutex_unlock(&array_mutex);

    //Note: Using a modern version of the Fisher-Yates shuffle to permutate
    //Generate random seed
    srand(time(NULL));

    for (int i = CUR_ARRAY_SIZE - 1; i > 0 ; i --){
        int j = (rand() % i );
        pthread_mutex_lock(&array_mutex);{
            swapElements(&ARRAY[i], &ARRAY[j]);
        }pthread_mutex_unlock(&array_mutex);
    }
    return; 
}

//Bubble sort the array in place
static void Sorter_sortArray(){
    for (int i = 0; i < CUR_ARRAY_SIZE - 1 ; i ++){
        for (int j = 0; j < CUR_ARRAY_SIZE - i - 1 ; j ++ ){
            pthread_mutex_lock(&array_mutex);{
                if (ARRAY[j] > ARRAY[j+1]){
                    swapElements(&ARRAY[j], &ARRAY[j+1]);
                }
            }pthread_mutex_unlock(&array_mutex);
        }
    }
    NUM_ARRAYS_SORTED ++;
    //Set next array size to be new size if it changed 
    CUR_ARRAY_SIZE = NEXT_ARRAY_SIZE;
    return;
}

//TODO Change the while(1) loop for an exit cond 
//Create array, shuffle it and sort 
static void* Sorter_initAndSort(void* arg){
    while(notDone){
        Sorter_createArray();
        Sorter_sortArray();
    }
    pthread_exit(0);
}


// ==== GLOBAL FUNCTIONS ==== //

// Setter for size of array
void Sorter_setArrayLength(int size){
    assert(size > 0 && size < 2100); 
    NEXT_ARRAY_SIZE = size;
    return; 
}

//Getter for size of array
int Sorter_getArrayLength(void){
    return CUR_ARRAY_SIZE;
}

//Return number of arrays that have completed sorting 
long long Sorter_getNumArraysSorted(void){
    return NUM_ARRAYS_SORTED; 
}


int* Sorter_getArrayData(int* length){
    int* arr = (int*) malloc(CUR_ARRAY_SIZE * sizeof(int));

    pthread_mutex_lock(&array_mutex);{
        *length = CUR_ARRAY_SIZE; 
        memcpy(arr, ARRAY, *length * sizeof(int)); 
    }pthread_mutex_unlock(&array_mutex);

    return arr;
}



//Initialize sorter Thread
void Sorter_start(void){

    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    int error = pthread_create(&tid, &attr, Sorter_initAndSort, NULL); 

    if (error != 0){
        printf("Sorter thread failed creation: %s\n", strerror(error));
    }else{
        printf("Sorter thread created successfully\n");
    }
    

}


//Stop Sorter Thread
void Sorter_stop(void){
    notDone = false; 

    pthread_join(tid, NULL);
    free(ARRAY);
}
