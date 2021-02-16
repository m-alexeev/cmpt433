#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h> 
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "./headers/display.h"

#define PORT 12345
#define MAX_LEN 1500

// static pthread_t  tid; 


// 1. Create Single threaded nework prog
// 2. Add Threading 

typedef struct Args{
    char name[15]; 
    char description[100];
}args;


static args commands[6] = {{"help\n", ""} , 
                           {"count\n", "-- display number arrays sorted.\n"},
                           {"get length\n", "-- display length of array currently being sorted.\n"},
                           {"get array\n", "-- display the full array being sorted.\n"},
                           {"get 10\n", "-- display the tenth element of array currently being sorted."},
                           {"stop\n" , "-- cause the server program to end."}};



static void getCommand(char* message){

    if (strcmp(commands[0].name, message) == 0){
        printf("HELP!\n");
    }else if (strcmp(commands[1].name, message) == 0){
        printf("COUNT\n");
    }else if (strcmp(commands[2].name, message) == 0){
        printf("LENGTH\n"); 
    }else if (strcmp(commands[3].name, message) == 0){
        printf("ARRAY\n");
    }else if (strcmp(commands[4].name, message) == 0){
        printf("10\n");
    }else if (strcmp(commands[5].name, message) == 0){
        printf("Stop\n"); 
    }
    

}


static void Display_listen(void){
    struct sockaddr_in sin;
    memset(&sin, 0 , sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    int socketDescriptor =  socket(PF_INET, SOCK_DGRAM, 0);
    bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

    while (1)
    {
        struct sockaddr_in sinRemote; 
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN];
        int bytesRx= recvfrom(socketDescriptor, 
                messageRx, MAX_LEN,0, 
                (struct sockaddr*) &sinRemote, &sin_len);

        int termIdx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termIdx] = 0;

		printf("Message received (%d bytes): '%s'\n", bytesRx, messageRx);

        // Get Command 
        getCommand(messageRx); 
      

        // Extract the value from the message:
		// (process the message any way your app requires).
		int incMe = atoi(messageRx);
        
        // Compose the reply message:
		// (NOTE: watch for buffer overflows!).
		char messageTx[MAX_LEN];
		sprintf(messageTx, "Math: %d + 1 = %d\n", incMe, incMe + 1);

		// Transmit a reply:
		sin_len = sizeof(sinRemote);
		sendto( socketDescriptor,
			messageTx, strlen(messageTx),
			0,
			(struct sockaddr *) &sinRemote, sin_len);
    }
    

}


void Display_start(void){
    Display_listen();
}


void Display_stop(void){

}



