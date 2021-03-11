#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


#include "headers/mixer.h"
#include "headers/controller.h"
#include "headers/input.h"

#define PORT 12345
#define MAX_LEN 25

//Threads
static pthread_t  tid; 
static bool notDone = true;
//Network
static int socketDescriptor;
static struct sockaddr_in sinRemote; 
static unsigned int sin_len;


#define TOKEN_MODE "mode"
#define TOKEN_VOLUME "volume"
#define TOKEN_TEMPO "tempo"
#define TOKEN_UPTIME  "uptime"
#define TOKEN_HAT "hihat"
#define TOKEN_SNARE "snare"
#define TOKEN_BASS "bass"


static void sendReply(char* message){
    sin_len = sizeof(sinRemote);
    sendto(socketDescriptor,
        message, MAX_LEN, 0, 
        (struct sockaddr *) &sinRemote, sin_len);
}


static void parseCommand(char* command){
    const char delim[2] = " ";
    char* token;
    
    token = strtok(command,delim);

    char buff[MAX_LEN];
    memset(buff, 0, MAX_LEN);
    while(token != NULL){
        if (strcmp(token, TOKEN_UPTIME)== 0){
            FILE* f = fopen("/proc/uptime", "r");
            fgets(buff,MAX_LEN, (FILE*)f);
            sendReply(buff);
            fclose(f);
        }
        if (strcmp(token, TOKEN_VOLUME) == 0){
            token = strtok(NULL, delim);
            if (token != NULL){
                strcmp(token,"up") == 0? Input_raiseVolume() : Input_lowerVolume();
            }                
            int vol = Mixer_getVolume();
            sprintf(buff,"%d\n", vol);
            sendReply(buff);
            return;
        }
        if (strcmp(token, TOKEN_TEMPO) == 0){
            token = strtok(NULL, delim);
            if (token != NULL){
                strcmp(token,"up") == 0 ? Input_raiseBPM() : Input_lowerBPM();
            }
            int bpm = Controller_getBPM();
            sprintf(buff, "%d\n", bpm);
            sendReply(buff);
            return;
        }
        if (strcmp(token, TOKEN_MODE) == 0){
            token = strtok(NULL,delim);
            if (token != NULL){
                int beat = atoi(token);
                Controller_setBeat(beat);
            }
            int beat = Controller_getBeat();
            sprintf(buff,"%d\n", beat);
            sendReply(buff);
            return;
        }
        if (strcmp(token,TOKEN_HAT) == 0){
            Controller_addBeat(HI_HAT);
        }
        if (strcmp(token,TOKEN_SNARE) == 0){
            Controller_addBeat(SNARE);
        }
        if (strcmp(token,TOKEN_BASS) == 0){
            Controller_addBeat(BASS);
        }
        return;
    }

}



static void*  Network_listen(void* args){
    struct sockaddr_in sin;
    memset(&sin, 0 , sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    socketDescriptor =  socket(PF_INET, SOCK_DGRAM, 0);
    bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));
    
    while (notDone)
    {
        sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN];
        int bytesRx= recvfrom(socketDescriptor, 
                messageRx, MAX_LEN,0, 
                (struct sockaddr*) &sinRemote, &sin_len);

        int termIdx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termIdx] = 0;

        //Parse the incoming command and send response message
        parseCommand(messageRx); 
        // printf("%s\n", messageRx);
    }
    pthread_exit(0);
}


void Network_start(void){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);
    
    int error = pthread_create(&tid, &attr, Network_listen, NULL); 
    if (error != 0){
        printf("Network thread failed creation %s\n", strerror(error));
    }else{
        printf("Network thread created successfully\n");
    }
}

void Network_stop(void){
    printf("Exiting network thread\n");

    pthread_join(tid, NULL);
    close(socketDescriptor);
}