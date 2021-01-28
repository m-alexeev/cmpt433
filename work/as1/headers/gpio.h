#ifndef GPIO_H_
#define GPIO_H_

//Write data to file 
void echo(int data);

// Function for sleeping before echoing
void wait(long seconds);

//Read data from a from Pin 
char*  readFromFileToScreen(char * fileName);

#endif