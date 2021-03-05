#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#define JOYSTICK_LEFT_PIN   65
#define JOYSTICK_RIGHT_PIN  47
#define JOYSTICK_UP_PIN     26
#define JOYSTICK_DOWN_PIN   46
#define JOYSTICK_PRESS_PIN  27

#define DIR_WRITING "out"
#define DIR_READING "in"

#define MODE_R "r"

#define JOYSTICK_FILE_PREFIX "/sys/class/gpio/gpio"


enum eJoystickDirection{
    DIRECTION_UP = 0,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_PRESS,
    NUM_DIRECTIONS,
    DIRECTION_NONE,
};


typedef struct JoystickDirectionInfo{
    const int JOYSTICK_DIRECTION; 
    const int pinNumber;
}JoystickDirInfo;


void Joystick_initialize(void);

int Joystick_read(char* filename);


int Joystick_getDirection();





#endif // !_JOYSTICK_H
