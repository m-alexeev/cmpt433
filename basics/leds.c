#include "headers/leds.h"

#define TRIGGER "/sys/class/leds/beaglebone:green:usr0/trigger"
#define BRIGHTNESS "/sys/class/leds/beaglebone:green:usr0/brightness"



void setTrigger(char* state){
	//TRigger stuff
	FILE *pLedTriggerFile = fopen(TRIGGER, "w");

	if (pLedTriggerFile == NULL){
		printf("ERROR OPENING %s,", TRIGGER);
		exit(1);
	}

	int charWritten = fprintf(pLedTriggerFile, state);
	if (charWritten <= 0){
		printf("ERROR WRITING DATA"); 
		exit(1); 
	}

	fclose(pLedTriggerFile); 
}



void setLED(char* state){
	//Brightness 
	FILE *pBrightness = fopen(BRIGHTNESS, "w");

	if (pBrightness == NULL){
		printf("ERROR OPENING %s,", BRIGHTNESS);
		exit(1);
	}

	int intWritten = fprintf(pBrightness, state);
	if (intWritten <= 0){
		printf("ERROR WRITING DATA"); 
		exit(1); 
	}

	fclose(pBrightness);
}
