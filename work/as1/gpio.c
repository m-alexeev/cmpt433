#include "headers/gpio.h"

#define EXPORT "/sys/class/gpio/export"

void echo(int data)
{
    FILE *pFile = fopen(EXPORT, "w");
    if (pFile == NULL)
    {
        printf("ERROR: Unable to open export file.\n");
        exit(1);
    }

    fprintf(pFile, "%d", data);
    fclose(pFile);
}

char* readFromFileToScreen(char *fileName)
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL)
    {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }
    // Read string (line)
    const int MAX_LENGTH = 1024;
    char* buff = malloc(MAX_LENGTH * sizeof(char));
    fgets(buff, MAX_LENGTH, pFile);
    // Close
    fclose(pFile);
    return buff;
}


