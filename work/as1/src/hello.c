#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "headers/leds.h"
#include "headers/gpio.h"
#include "headers/utils.h"


static char file[4][50] = {
		"/sys/class/gpio/gpio26/value",
		"/sys/class/gpio/gpio46/value",
		"/sys/class/gpio/gpio47/value",
		"/sys/class/gpio/gpio65/value",
};


//Generate random number between 0 and 1
static int targetPicker(){
	srand(time(0));
	int random = rand() % 2;
	return random;
}



int main()
{

	printf("Hello embedded world, from Mikhail Alexeev\n");

	printf("Press the Zen cape's Joystick in the direction of the LED.\nUP for LED 0 (top)\nDOWN for LED 3 (bottom)\nLEFT/RIGHT for exit app.\n");



	resetLEDS();
	int cur_score = 0;
	int rounds = 9;
	int dir = 0;

	//TODO
	//Print cur score (0)
	for (int i = 0; i < rounds; i++){
		int rand = targetPicker();

		rand == 0 ? setLED(0,"1") : setLED(3,"1");

		int input = 0;
		printf("Press joystick; current score (%d / %d)\n", cur_score, rounds);

		//Check that joystick is released
		while(atoi(readFromFileToScreen(file[dir])) == 0){}

		//Check for js input
		while (input < 1){
			//AWAIT INPUT ON PINS 26U 47R 46D 65L		
			for (int i = 0; i < 4; i ++){
				if (atoi(readFromFileToScreen(file[i]))== 0){
					dir = i;
					input = 1;
				}
			}

		}
		//1E8 nanoseconds == 0.1 seconds 
		
		long blinkDuration = 1E8;
		//Joystick stuff
		if (dir == rand){
			setLEDBlink(blinkDuration, 1);
			cur_score++;
			printf("Correct!\n");
		}

		else if (dir < 2){
			printf("Incorrect\n");
			setLEDBlink(blinkDuration, 5);
		}
		
		else{
			printf("Exiting the app!\n");
			break;
		}
		resetLEDS();

	}
	printf("Your final score was (%d / %d)\n", cur_score, rounds);
	printf("Thank you for playing\n");
	return 0;
}
