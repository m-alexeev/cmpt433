#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/util.h"

#define EXPORT "/sys/class/gpio/export"


void sleepSecs(float seconds)
{
    struct timespec reqDelay = {seconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}