#include <stdio.h>
#include <stdlib.h>

// Set Trigger state ex. None, heartbeat etc.
void setTrigger(int LED, char * state);

// Turn LED ON / OFF , possible states : "0"/"1"
void setLED(int LED, char* state); 

// Turn LED Delay on
void setLEDDelay(int LED, char* delay, int state);
