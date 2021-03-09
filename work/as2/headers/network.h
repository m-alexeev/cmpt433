#ifndef _NETWORK_H_
#define _NETWORK_H_

/*
    Threaded Network module, recieves commands on a UDP socket and 
    sends back a UDP response to the sender
*/


void Network_start(void);
void Network_stop(void);

#endif