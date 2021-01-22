#include "headers/utils.h"


void wait(long seconds)
{
    long nanoseconds = 500000000;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}