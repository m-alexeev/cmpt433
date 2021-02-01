#ifndef UTILS_H_
#define UTILS_H_ 

//Sleep for n seconds (can also do fractions of a second)
void wait(long seconds, long nanoseconds);

// Read data from file 
char* readFromFile(char *fileName); 

//Write data to file 
void echo(int data);

#endif 