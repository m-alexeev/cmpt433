#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/util.h"

#define EXPORT "/sys/class/gpio/export"


void Util_sleepForSeconds(float seconds)
{
    struct timespec reqDelay = {seconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}