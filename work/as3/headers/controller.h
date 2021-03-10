#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

enum eBeat{
    NO_BEAT = 0,
    ROCK_BEAT,
    CUSTOM_BEAT,
};

void Controller_start(void);

void Controller_stop(void);

void Controller_addBeat(int direction);

void Controller_setBPM(int bpm);

int Controller_getBPM(void);

void Controller_setBeat(int bpm);

int Controller_getBeat(void);

#endif // !_MUSIC