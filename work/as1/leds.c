#include "headers/leds.h"
#include "headers/utils.h"

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


void setLEDBlink(long duration, int rounds){    
    //Turn all LEDS OFF
    for (int i = 0; i < 4; i ++){
        setLED(i,"0");
    }
    // Blink round number of times 
    for (int round = 0; round < rounds; round ++){

        //Turn ALL leds ON 
        for (int i = 0; i < 4; i ++){
            setLED(i, "1");
        }
        wait(duration); 
        //Turn ALL LEDS OFF After duration ms 
        for (int i = 0; i < 4; i ++){
            setLED(i, "0");
        }
        wait(duration);
    } 
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
