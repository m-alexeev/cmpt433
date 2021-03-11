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
    while(token != NULL){
        if (strcmp(token, TOKEN_UPTIME)== 0){
            FILE* f = fopen("/proc/uptime", "r");
            char buff[MAX_LEN];
            memset(buff, 0, MAX_LEN);
            fgets(buff,MAX_LEN, (FILE*)f);
            sendReply(buff);
            fclose(f);
            return;
        }
        if (strcmp(token, TOKEN_VOLUME) == 0){
            token = strtok(NULL, delim);
            if (token == NULL){
                //return cur volume 
            }else{
                //parse and update volume
            }
            return;
        }
        if (strcmp(token, TOKEN_TEMPO) == 0){
            token = strtok(NULL, delim);
            if (token == NULL){
                //return cur tempo
            }else{
                //parse and update tempo
            }
            return;
        }
        if (strcmp(token, TOKEN_MODE) == 0){
            token = strtok(NULL,delim);
            if (token == NULL){
                //return current mode
            }else{
                //parse to int and set mode
            }
            return;
        }
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