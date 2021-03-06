#ifndef _INPUT_H_
#define _INPUT_H_ 
#include <stdint.h>

typedef struct Accelerometer_t{
    int16_t x;
    int16_t y;
    int16_t z;
}Accelerometer_t;


#define HOLD_INTERVAL 5E8


void Input_start(void);

void Input_stop(void);

#endif // !_INPUT_H_
