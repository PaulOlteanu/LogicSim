#ifndef CSVREAD_C_INCLUDE
#define CSVREAD_C_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Make these enums
typedef struct pinRow {
    int type; // 0: out. 1: in
    int number; // 1-14
    int net; // Any number
} pinRow;

typedef struct netRow {
    int net; // Any number
    int type; // 0: and. 1: or. 2: xor. 3: nand
} netRow;

int readPins(char *filename, pinRow **pinData, int *numRows) {
    *numRows = 0;

    const int BUFFER_SIZE = 2048;

    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    while(!feof(file)) {
        char ch = fgetc(file);
        if(ch == '\n') {
            (*numRows)++;
        }
    }

    rewind(file);
    
    *pinData = malloc((*numRows) * sizeof(pinRow));

    char typeString[BUFFER_SIZE];
    char numberString[BUFFER_SIZE];
    char netString[BUFFER_SIZE];

    char *target[3];
    target[0] = typeString;
    target[1] = numberString;
    target[2] = netString;
    int targetNumber = 0;
    int targetIndex = 0;

    char buffer[BUFFER_SIZE];

    int rowNumber = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        rowNumber++;
        for(int i = 0; i < strlen(buffer) - 1; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\t') {
                continue;
            } else if (buffer[i] == ',') {
                targetIndex++;
                target[targetNumber][targetIndex] = '\0';

                targetNumber++;
                if (targetNumber > 2) {
                    return -1;
                }

                targetIndex = 0;
            } else if (buffer[i] < '0' || buffer[i] > '9') {
                return -1;
            } else {
                target[targetNumber][targetIndex] = buffer[i];
            }
        }

        (*pinData)[rowNumber - 1].type = atoi(typeString); 
        (*pinData)[rowNumber - 1].number = atoi(numberString); 
        (*pinData)[rowNumber - 1].net = atoi(netString); 
    }
    return 0;
}

#endif
