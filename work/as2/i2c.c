#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "./headers/i2c.h"


//Threading
static pthread_t tid; 
static pthread_attr_t attr; 
