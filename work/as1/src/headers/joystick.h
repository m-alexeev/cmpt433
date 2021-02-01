#ifndef JOYSTICK_H_
#define JOYSTICK_H_


typedef enum eJoystickDirections{
    JOYSTICK_UP = 0,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    JOYSTICK_PRESSED,
    JOYSTICK_MAX_DIRECTIONS
} eJoystickDirections;


//Checks if any of the joystick buttons is pressed
bool Joystick_isPressed();


//CHecks if a specific Joystick button is pressed
bool Joystick_isDirectionPressed(eJoystickDirections direction); 



#endif