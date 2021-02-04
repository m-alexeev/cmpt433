#ifndef SORTER_H_
#define SORTER_H_


// Begin/end the background thread which sorts random permutations.
void Sorter_startSorting(void); 
void Sorter_stopSorting(void);


// Set size of the array 
void Sorter_setArraySize(int size);

// Returns size of array
int Sorter_getArraySize(void);

// Create the array
int* Sorter_initializeArray(int size); 

// Sorts array using bubble sort 
void Sorter_sortArray(void); 

//Frees the space used by the array after it is done being used
void Sorter_freeArray(void); 

//Get a copy of the array and return a copy of the current potentially sorted array
int* Sorter_getArrayData(int *length); 


// Get number of arrays that have been sorted
long long Sorter_getNumberArraysSorted(void); 


#endif // !ARRAYCONTROLLER_H_
