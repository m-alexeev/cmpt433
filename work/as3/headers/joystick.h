#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_ 


#define JOYSTICK_LEFT_PIN   65
#define JOYSTICK_RIGHT_PIN  47
#define JOYSTICK_UP_PIN     26
#define JOYSTICK_DOWN_PIN   46
#define JOYSTICK_PRESS_PIN  27

#define DIR_WRITING "out"
#define DIR_READING "in"

#define JOYSTICK_FILE_PREFIX "/sys/class/gpio/gpio"

enum JOYSTICK_DIRECTION{
    DIRECTION_UP = 0,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_PRESS,
    JOYSTICK_COUNT,
};


typedef struct JoystickDirectionInfo{
    const int JOYSTICK_DIRECTION; 
    const int pinNumber;
}JoystickDirInfo;


void Joystick_start(void);

void Joystick_stop(void);

#endif // !_JOYSTICK_H_
