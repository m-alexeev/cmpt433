#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_ 


#define JOYSTICK_LEFT 65
#define JOYSTICK_RIGHT 47
#define JOYSTICK_UP   26
#define JOYSTICK_DOWN 46
#define JOYSTICK_PRESS 27

#define DIRECTION_OUT "out"
#define DIRECTION_IN "in"

enum JOYSTICK_DIRECTION{
    DIRECTION_UP = 0,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_PRESS,
};



void Joystick_start(void);

void Joystick_stop(void);

#endif // !_JOYSTICK_H_
