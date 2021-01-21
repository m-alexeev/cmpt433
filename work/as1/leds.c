#include "headers/leds.h"

const char TRIGGERS[4][50] = {
    "/sys/class/leds/beaglebone:green:usr0/trigger",
    "/sys/class/leds/beaglebone:green:usr1/trigger",
    "/sys/class/leds/beaglebone:green:usr2/trigger",
    "/sys/class/leds/beaglebone:green:usr3/trigger",
};

const char BRIGHTNESS[4][50] = {
    "/sys/class/leds/beaglebone:green:usr0/brightness",
    "/sys/class/leds/beaglebone:green:usr1/brightness",
    "/sys/class/leds/beaglebone:green:usr2/brightness",
    "/sys/class/leds/beaglebone:green:usr3/brightness"
};

const char DELAY_ON[4][50] = {
    "/sys/class/leds/beaglebone:green:usr0/delay_on",
    "/sys/class/leds/beaglebone:green:usr1/delay_on",
    "/sys/class/leds/beaglebone:green:usr2/delay_on",
    "/sys/class/leds/beaglebone:green:usr3/delay_on"
};

const char DELAY_OFF[4][50] = {
    "/sys/class/leds/beaglebone:green:usr0/delay_off",
    "/sys/class/leds/beaglebone:green:usr1/delay_off",
    "/sys/class/leds/beaglebone:green:usr2/delay_off",
    "/sys/class/leds/beaglebone:green:usr3/delay_off"
};

void setTrigger(int LED, char* state){
	//TRigger stuff

    FILE *pLedTriggerFile = fopen(TRIGGERS[LED], "w");

	if (pLedTriggerFile == NULL){
		printf("ERROR OPENING %s.\n", TRIGGERS[LED]);
		exit(1);
	}

	int charWritten = fprintf(pLedTriggerFile, state);
	if (charWritten <= 0){
		printf("ERROR WRITING DATA.\n"); 
		exit(1); 
	}

	fclose(pLedTriggerFile); 
}


void setLEDDelay(int LED, char* delay, int state){

    FILE *pDelay;

    pDelay = state == 0 ? fopen(DELAY_OFF[LED],"w") : fopen(DELAY_ON[LED], "w");

    if (pDelay == NULL){
        state == 0 ? printf("ERROR OPENING %s", DELAY_OFF[LED]) : printf("ERROR OPENING %s", DELAY_ON[LED]);
    }
    int charWritten = fprintf(pDelay, delay);
	if (charWritten <= 0){
		printf("ERROR WRITING DATA.\n"); 
		exit(1); 
	}
    fclose(pDelay);

}


void setLED(int LED, char* state){
	//Brightness 
	FILE *pBrightness = fopen(BRIGHTNESS[LED], "w");

	if (pBrightness == NULL){
		printf("ERROR OPENING %s.\n", BRIGHTNESS[LED]);
		exit(1);
	}

	int intWritten = fprintf(pBrightness, state);
	if (intWritten <= 0){
		printf("ERROR WRITING DATA.\n"); 
		exit(1); 
	}

	fclose(pBrightness);
}
