#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/util.h"

#define EXPORT "/sys/class/gpio/export"


void Util_sleepForSeconds(float seconds, long nanoseconds)
{
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}

