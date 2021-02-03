#ifndef ARRAYCONTROLLER_H_
#define ARRAYCONTROLLER_H_


// Set size of the array 
void setArraySize(int size);

// Returns size of array
int getArraySize(void);

// Create the array
int* initializeArray(int size); 

// Sorts array using bubble sort 
int* sortArray(); 

//Frees the space used by the array after it is done being used
void freeArray(int* arr); 

#endif // !ARRAYCONTROLLER_H_
