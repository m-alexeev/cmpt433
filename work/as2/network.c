#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h> 
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "./headers/network.h"
#include "./headers/sorter.h"
#include "./headers/shutdown.h"

#define PORT 12345
#define MAX_LEN 400

//Threads
static pthread_t  tid; 
static bool notDone = true;
//Network
static int socketDescriptor;
static struct sockaddr_in sinRemote; 
static unsigned int sin_len;


static void sendReply(char* message){
    sin_len = sizeof(sinRemote);
    sendto( socketDescriptor,
        message, MAX_LEN, 0,
        (struct sockaddr *) &sinRemote, sin_len);
}

static void sendHelpText(){
    char MESSAGE_TX[MAX_LEN] = "Accepted command examples:\
    \ncount       -- display number arrays sorted.\
    \nget length  -- display length of array currently being sorted.\
    \nget array   -- display the full array being sorted.\
    \nget 10      -- display the tenth element of array currently being sorted.\
    \nstop        -- cause the server program to end.\n";
    sendReply(MESSAGE_TX);
}

static void sendCountText(){
    char MESSAGE_TX[MAX_LEN];
    memset(MESSAGE_TX,0,MAX_LEN);
    sprintf(MESSAGE_TX, "Number of arrays sorted %llu\n", Sorter_getNumArraysSorted());
    sendReply(MESSAGE_TX);
}

static void sendArrayText(){
    char MESSAGE_TX[MAX_LEN];
    memset(MESSAGE_TX,0,MAX_LEN);

    int len = Sorter_getArrayLength();
    int * temparr = Sorter_getArrayData(&len);
    int messageLen = 0;
    for (int i = 0; i < len; i ++){
        if (MAX_LEN - messageLen < 7){
            sendReply(MESSAGE_TX);
            memset(MESSAGE_TX, 0, MAX_LEN);
            messageLen = 0;
        }
        if (i == len - 1){
            messageLen += sprintf(MESSAGE_TX + messageLen, "%d\n",temparr[i]);
        } 
        else if (i > 0 && i % 10 == 0){
            messageLen += sprintf(MESSAGE_TX + messageLen, "%d,\n",temparr[i]);
        } 
        else{
            messageLen += sprintf(MESSAGE_TX + messageLen, "%d, ",temparr[i]);
        }
    }
    sendReply(MESSAGE_TX);
    free(temparr);
}

static void sendArrayData(int index){
    char MESSAGE_TX[MAX_LEN];
    memset(MESSAGE_TX,0,MAX_LEN);

    int len; 
    int * temp = Sorter_getArrayData(&len);
    if (index < 1 || index > len){
        sprintf(MESSAGE_TX,"Invalid argument. Must be between 1 and %d (array length)\n", len);
    }else{
        sprintf(MESSAGE_TX,"Value %d = %d\n",index ,temp[index - 1]);
    }
    sendReply(MESSAGE_TX);
}

static void sendArrayLength(){
    char MESSAGE_TX[MAX_LEN];
    memset(MESSAGE_TX,0,MAX_LEN);

    sprintf(MESSAGE_TX, "Current array length = %d\n", Sorter_getArrayLength());
    sendReply(MESSAGE_TX);
}

static void sendStop(){
    char MESSAGE_TX[MAX_LEN];
    memset(MESSAGE_TX,0,MAX_LEN);

    sprintf(MESSAGE_TX, "Program Terminating\n");
    sendReply(MESSAGE_TX);
}

static void parseCommand(char* message){

    const char delim[2] = " "; 
    char * token; 
    bool get = false; 

    token = strtok(message, delim);
    while (token != NULL){
        if (!get && strcmp(token, "help\n") == 0){
            sendHelpText();
        }
        if (!get && strcmp(token, "count\n") == 0){
            sendCountText();
        }

        if (get && (strcmp(token, "array\n") == 0)){
            sendArrayText();
        }else if (get && (strcmp(token, "length\n") == 0)){
            sendArrayLength();
        }else if (get){
            int index = atoi(token);
            sendArrayData(index);
        }
        if (strcmp(token, "get") == 0){
            get = true;
        }

        if (!get && strcmp(token, "stop\n") == 0){
            sendStop();
            Shutdown_trigger();
        }

        token = strtok(NULL, delim);
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
    notDone = false;
    printf("Exiting network thread\n");

    pthread_join(tid, NULL);
    close(socketDescriptor);
}



