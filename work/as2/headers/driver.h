#ifndef _DRIVER_H_
#define _DRIVER_H_

/*
    Module for controlling the knob and setting the I2C display digits 
    Synchronizes readings to 1 reading / seconds
*/


//Start driver thread
void Driver_start(void);

//Stop driver thread
void Driver_stop(void);


#endif // !_DRIVER_H
