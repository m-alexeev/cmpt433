#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t exit_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  exit_cond = PTHREAD_COND_INITIALIZER;

static bool shutdown = false;


//Used cmpt300 for reference
void Shutdown_wait(){
    pthread_mutex_lock(&exit_mutex);{
        while(!shutdown){
            pthread_cond_wait(&exit_cond, &exit_mutex);
        }
    }
    pthread_mutex_unlock(&exit_mutex);
}


void Shutdown_trigger(){
    pthread_mutex_lock(&exit_mutex);{
        shutdown = true; 
        pthread_cond_signal(&exit_cond);
    }
    pthread_mutex_unlock(&exit_mutex);
}
