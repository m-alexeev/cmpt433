#ifndef _INPUT_H_
#define _INPUT_H_ 
#include <stdint.h>

typedef struct Accelerometer_t{
    int16_t x;
    int16_t y;
    int16_t z;
}Accelerometer_t;


#define POLL_RATE 1E7
#define DEBOUNCE_JOYSTICK 3E8
#define DEBOUNCE_ACCEL 3E8


void Input_start(void);

void Input_stop(void);

#endif // !_INPUT_H_
