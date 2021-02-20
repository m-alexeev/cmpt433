#ifndef _KNOB_H_
#define _KNOB_H_

// void Knob_start(void);
// void Knob_stop(void);

//Get current output voltage from the pot
int Knob_getVoltage0Reading(void);

//Calculate array size based on reading
int Knob_calculateArraySize(int reading);


#endif