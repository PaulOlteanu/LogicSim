#ifndef CSVREAD_C_INCLUDE
#define CSVREAD_C_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum PIN_TYPE {IN, OUT} PIN_TYPE;
typedef enum NET_TYPE {AND, OR, XOR, NAND} NET_TYPE;

typedef struct pin {
    PIN_TYPE type;
    int number; // 1-14
    int net; // Any number
} pin;

typedef struct net {
    int net; // Any number
    NET_TYPE type;
    pin *pins;
    int numPins;
} net;

int numberOfRows(FILE *file) {
    int numRows = 0;
    while(!feof(file)) {
        char ch = fgetc(file);
        if(ch == '\n') {
            numRows++;
        }
    }
    rewind(file);

    return numRows;
}

int readPins(char *filename, pin **pins, int *numRows) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    *numRows = numberOfRows(file);
    *pins = malloc((*numRows) * sizeof(pin));

    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    char typeString[BUFFER_SIZE];
    char numberString[BUFFER_SIZE];
    char netString[BUFFER_SIZE];

    memset(buffer, 0, sizeof buffer);
    memset(typeString, 0, sizeof typeString);
    memset(numberString, 0, sizeof numberString);
    memset(netString, 0, sizeof netString);

    char *target[3];
    target[0] = typeString;
    target[1] = numberString;
    target[2] = netString;
    int targetNumber = 0;
    int targetIndex = 0;

    int rowNumber = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        targetNumber = 0;
        targetIndex = 0;
        for(int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\n') {
                break;
            } else if (buffer[i] == ' ' || buffer[i] == '\t') {
                continue;
            } else if (buffer[i] == ',') {
                targetIndex++;
                target[targetNumber][targetIndex] = '\0';

                targetNumber++;
                if (targetNumber > 2) {
                    fclose(file);
                    return -1;
                }

                targetIndex = 0;
            } else if (buffer[i] < '0' || buffer[i] > '9') {
                fclose(file);
                return -1;
            } else {
                target[targetNumber][targetIndex] = buffer[i];
            }
        }

        // TODO: Best practices is to initialize these with something
        int pinType = atoi(typeString);
        switch (pinType) {
            case 0:
            (*pins)[rowNumber].type = IN; 
            break;
            case 1:
            (*pins)[rowNumber].type = OUT; 
            break;
            default:
            return -1;
        }
        (*pins)[rowNumber].number = atoi(numberString); 
        (*pins)[rowNumber].net = atoi(netString); 

        rowNumber++;
    }

    fclose(file);
    return 0;
}

int readNets(char *filename, net **nets, int *numRows) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    *numRows = numberOfRows(file);
    *nets = malloc((*numRows) * sizeof(net));

    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    char netString[BUFFER_SIZE];
    char typeString[BUFFER_SIZE];
    memset(buffer, 0, sizeof buffer);
    memset(netString, 0, sizeof netString);
    memset(typeString, 0, sizeof typeString);

    char *target[2];
    target[0] = netString;
    target[1] = typeString;
    int targetNumber = 0;
    int targetIndex = 0;

    int rowNumber = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        targetNumber = 0;
        targetIndex = 0;
        for(int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\n') {
                break;
            } else if (buffer[i] == ' ' || buffer[i] == '\t') {
                continue;
            } else if (buffer[i] == ',') {
                targetIndex++;
                target[targetNumber][targetIndex] = '\0';

                targetNumber++;
                if (targetNumber > 1) {
                    fclose(file);
                    return -1;
                }

                targetIndex = 0;
            } else if (buffer[i] < '0' || buffer[i] > '9') {
                fclose(file);
                return -1;
            } else {
                target[targetNumber][targetIndex] = buffer[i];
            }
        }

        // TODO: Best practices is to initialize these with something
        int netType = atoi(typeString);
        switch (netType) {
            case 1:
            (*nets)[rowNumber].type = AND; 
            break;
            case 2:
            (*nets)[rowNumber].type = OR; 
            break;
            case 3:
            (*nets)[rowNumber].type = XOR; 
            break;
            case 4:
            (*nets)[rowNumber].type = NAND; 
            break;
            default:
            return -1;
        }
        (*nets)[rowNumber].net = atoi(netString); 
        rowNumber++;
    }

    fclose(file);
    return 0;
}

int initNets(net *nets, pin *pins, int numPins, int numNets) {
    for (int i = 0; i < numNets; i++) {
        nets[i].numPins = 0;
        nets[i].pins = NULL;
    }

    int found;

    for (int i = 0; i < numPins; i++) {
        int net = pins[i].net;
        found = 0;

        for (int j = 0; j < numNets; j++) {
            if (nets[j].net == net) {
                found = 1;
                nets[j].numPins++;
                if (nets[j].numPins > 1) {
                    pin *temp = nets[j].pins;
                    nets[j].pins = malloc(nets[j].numPins * sizeof(pin));
                    for (int k = 0; k < nets[j].numPins - 1; k++) {
                        nets[j].pins[k] = temp[k];
                    }
                    free(temp);
                    nets[j].pins[numPins - 1] = pins[i];
                } else {
                    nets[j].pins = malloc(nets[j].numPins * sizeof(pin));
                    nets[j].pins[0] = pins[i];
                }
            }
        }

        if (!found) {
            printf("FOUND: %d", found);
            return -1;
        }
    }
    return 0;
}

#endif
