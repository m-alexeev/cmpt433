#ifndef _KNOB_H_
#define _KNOB_H_

/*
    Module for reading the POT on the Zencape and transforming the readings into 
    The piecewise array
*/

//Get current output voltage from the pot
int Knob_getVoltage0Reading(void);

//Calculate array size based on reading
int Knob_calculateArraySize(int reading);


#endif