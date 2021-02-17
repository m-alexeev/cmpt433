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
#define MAX_LEN 1500

static pthread_t  tid; 
static int socketDescriptor;


typedef struct Args{
    char name[15]; 
    char description[100];
}args;


static args commands[5] = {{"count",  "-- display number arrays sorted.\n"},
                           {"get length",  "-- display length of array currently being sorted.\n"},
                           {"get array",  "-- display the full array being sorted.\n"},
                           {"get 10",  "-- display the tenth element of array currently being sorted.\n"},
                           {"stop", "-- cause the server program to end.\n"}};




static void printHelp(void){
    printf("Accepted command examples:\n");
    for (int i =0 ; i < 5; i ++ ){
        printf("%-10s %-30s", commands[i].name, commands[i].description);    
    }
}


static void parseCommand(char* message, int len){

    const char delim[2] = " "; 
    char * token; 

    bool get = false; 
    token = strtok(message, delim);
    while (token != NULL){
        if (strcmp(token, "help\n") == 0){
            printHelp();
        }
        if (strcmp(token, "count\n") == 0){
            printf("Number of arrays sorted = %llu\n",Sorter_getNumArraysSorted());        
        }
        if (strcmp(token, "stop\n") == 0){
            printf("STOP!\n");
        }
        if (get && (strcmp(token, "array\n") == 0)){
            int * temparr = Sorter_getArrayData(&len);
            for (int i = 0; i < len; i ++){
                //1. Send back the data to the requeting entity 
                    
                printf("%d ", temparr[i]);
            }
            printf("\n");
            free(temparr);
        }
        if (get && (strcmp(token, "length\n") == 0)){
            printf("Current array length = %d\n",Sorter_getArrayLength()); 
        }
        
        if (get && atoi(token) != 0){
            int index = atoi(token);

            int len; 
            int * temp = Sorter_getArrayData(&len);
            printf("%d\n", len);
            if (index < 1 || index > len){
                printf("get index is out of bounds\n");

            }else{
                printf("%d\n", temp[index - 1]);
            }

        }
        if (strcmp(token, "get") == 0){
            get = true;
        }

        token = strtok(NULL, delim);
    }

    // if (strcmp(commands[0].cmp, message) == 0){
    //     printf("Accepted command examples:\n");
    //     for (int i = 1; i < 6; i ++){
    //         printf("%-10s %-30s", commands[i].name, commands[i].description);
    //     }    
    // }else if (strcmp(commands[1].cmp, message) == 0){
    // }else if (strcmp(commands[2].cmp, message) == 0){
    //     printf("%d\n",Sorter_getArrayLength()); 
    // }else if (strcmp(commands[3].cmp, message) == 0){
    //     int len; 
    //     int * temparr = Sorter_getArrayData(&len);
    //     for (int i = 0; i < len; i ++){
    //         //1. Send back the data to the requeting entity 
    //         printf("%d ", temparr[i]);
    //     }
    //     printf("\n");
    //     free(temparr);
    // }else if (strcmp(commands[4].cmp, message) == 0){
    //     int len; 
    //     int* temparr = Sorter_getArrayData(&len);
    //     printf("%d is the 10th element\n", temparr[9]);
    //     free(temparr);
    // }else if (strcmp(commands[5].cmp, message) == 0){
    //     printf("Stop\n"); 
    //     //Stop the program and all the Threads
    // }
    

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
        struct sockaddr_in sinRemote; 
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN];
        int bytesRx= recvfrom(socketDescriptor, 
                messageRx, MAX_LEN,0, 
                (struct sockaddr*) &sinRemote, &sin_len);

        int termIdx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termIdx] = 0;

        //Parse the incoming command 
        parseCommand(messageRx, termIdx); 
      
        
        // Compose the reply message:
		// (NOTE: watch for buffer overflows!).
		char messageTx[MAX_LEN];

		// Transmit a reply:
		sin_len = sizeof(sinRemote);
		sendto( socketDescriptor,
			messageTx, strlen(messageTx),
			0,
			(struct sockaddr *) &sinRemote, sin_len);
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



