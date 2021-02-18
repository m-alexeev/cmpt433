#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h> 
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "./headers/display.h"
#include "./headers/sorter.h"

#define PORT 12345
#define MAX_LEN 400

static pthread_t  tid; 
static int socketDescriptor;
static struct sockaddr_in sinRemote; 
static unsigned int sin_len;

typedef struct Args{
    char name[15]; 
    char description[100];
}args;


static args commands[5] = {{"count",  "-- display number arrays sorted.\n"},
                           {"get length",  "-- display length of array currently being sorted.\n"},
                           {"get array",  "-- display the full array being sorted.\n"},
                           {"get 10",  "-- display the tenth element of array currently being sorted.\n"},
                           {"stop", "-- cause the server program to end.\n"}};



static void sendReply(char* message){
    sin_len = sizeof(sinRemote);
    sendto( socketDescriptor,
        message, MAX_LEN, 0,
        (struct sockaddr *) &sinRemote, sin_len);
}


static void parseCommand(char* message, int len){

    const char delim[2] = " "; 
    char * token; 
    bool get = false; 
    
    char messageTx[MAX_LEN];
    memset(messageTx,0,MAX_LEN);

    token = strtok(message, delim);
    while (token != NULL){
        if (!get && strcmp(token, "help\n") == 0){
            int len = 0;
            len += sprintf(messageTx, "Accepted command examples:\n");
            for (int i = 0; i < 5; i ++){
                len += sprintf(messageTx + len, "%-10s %-30s", commands[i].name, commands[i].description);
            }
            sendReply(messageTx);
        }
        if (!get && strcmp(token, "count\n") == 0){
            sprintf(messageTx, "Number of arrays sorted %llu\n", Sorter_getNumArraysSorted());
            sendReply(messageTx);
        }
        if (!get && strcmp(token, "stop\n") == 0){
            sprintf(messageTx, "Program Terminating\n");
            sendReply(messageTx);
        }
        if (get && (strcmp(token, "array\n") == 0)){
            int * temparr = Sorter_getArrayData(&len);
            int messageLen = 0;
            for (int i = 0; i < len; i ++){
                if (MAX_LEN - messageLen < 7){
                    sendReply(messageTx);
                    memset(messageTx, 0, MAX_LEN);
                    messageLen = sprintf(messageTx, "%d, ", temparr[i]);
                }else{
                    if (i < len - 1 && i > 0 && i % 10 == 0){
                        messageLen += sprintf(messageTx + messageLen, "%d,\n",temparr[i]);
                    }else if (i == len - 1){
                        messageLen += sprintf(messageTx + messageLen, "%d\n",temparr[i]);
                    } 
                    else{
                        messageLen += sprintf(messageTx + messageLen, "%d, ",temparr[i]);
                    }
                }
            }
            sendReply(messageTx);
            free(temparr);
        }else if (get && (strcmp(token, "length\n") == 0)){
            sprintf(messageTx, "Current array length = %d\n", Sorter_getArrayLength());
            sendReply(messageTx);
        }else if (get){
            int index = atoi(token);
            int len; 
            int * temp = Sorter_getArrayData(&len);
            if (index < 1 || index > len){
                sprintf(messageTx,"Invalid argument. Must be between 1 and %d (array length)\n", len);
            }else{
                sprintf(messageTx,"%d\n", temp[index - 1]);
            }
            sendReply(messageTx);
        }
        if (strcmp(token, "get") == 0){
            get = true;
        }

        token = strtok(NULL, delim);
    }
   

}


static void*  Display_listen(void* args){
    struct sockaddr_in sin;
    memset(&sin, 0 , sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    socketDescriptor =  socket(PF_INET, SOCK_DGRAM, 0);
    bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));
    bool notDone = true; 
    
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
        parseCommand(messageRx, termIdx); 

    }
    pthread_exit(0);

}


void Display_start(void){
    pthread_attr_t attr; 
    pthread_attr_init(&attr);
    
    int error = pthread_create(&tid, &attr, Display_listen, NULL); 
    if (error != 0){
        printf("Network thread failed creation %s\n", strerror(error));
    }else{
        printf("Network thread created successfully\n");
    }

}


void Display_stop(void){
    close(socketDescriptor);
    pthread_join(tid, NULL);
}



