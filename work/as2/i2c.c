#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "./headers/i2c.h"


//Threading
static pthread_t tid; 
static pthread_attr_t attr; 

void* TestFunct(void* arg){
    long* limit_ptr = (long *)arg; 
    long limit = *limit_ptr; 
    free(limit_ptr);

    long sum = 0;
    for (int i = 0; i < limit; i ++){
        sum += i;
    }
    printf("sum = %ld", sum);
    pthread_exit(0);
}


void Test_threadStart(){
    long limit = 100000;
    pthread_attr_init(&attr); 
    pthread_create(&tid, &attr, TestFunct, &limit); 

}


void Test_threadStop(void){
    pthread_join(tid, NULL);

}