#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include "./headers/arrayController.h"

int main(int argc, char* argv[]){
    int* arr = initializeArray(10);
    freeArray(arr);
}