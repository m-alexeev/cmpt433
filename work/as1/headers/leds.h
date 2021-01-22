#include <stdio.h>
#include <stdlib.h>

// Set Trigger state ex. None, heartbeat etc.
void setTrigger(int LED, char * state);

// Turn LED ON / OFF , possible states : "0"/"1"
void setLED(int LED, char* state); 

// Blink ALL LEDs for duration seconds , rounds number of times
void setLEDBlink(long duration, int rounds);
