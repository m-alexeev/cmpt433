#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/utils.h"


void wait(long seconds, long nanoseconds)
{
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}