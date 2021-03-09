#ifndef SHUTDOWN_H
#define SHUTDOWN_H

/*
    Shutdown module, blocks main thread from exiting until the trigger is 
    activated
*/


void Shutdown_wait(void);
void Shutdown_trigger(void);


#endif // !SHUTDOWN_H