#ifndef FILEREAD_C_INCLUDE
#define FILEREAD_C_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileRead.h"
#include "Net.h"
#include "Pin.h"
#include "Logging.h"

int numberOfRows(FILE *file) {
    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];

    int numRows = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (!(buffer[0] == '\n' || (strlen(buffer) > 2 && buffer[0] == '/' && buffer[1] == '/'))) {
            numRows++;
        }
    }

    rewind(file);
    return numRows;
}

int readPins(char *filename, pin **pins, int *numRows, char *logFile, int debugMode) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        logMessage(logFile, ERROR, "Could not open pin file\n");
        return -1;
    }

    *numRows = numberOfRows(file);
    *pins = malloc((*numRows) * sizeof(pin));

    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    char typeString[BUFFER_SIZE];
    char numberString[BUFFER_SIZE];
    char netString[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    memset(typeString, 0, sizeof(typeString));
    memset(numberString, 0, sizeof(numberString));
    memset(netString, 0, sizeof(netString));

    char *target[3];
    target[0] = typeString;
    target[1] = numberString;
    target[2] = netString;
    int targetNumber = 0;
    int targetIndex = 0;

    int rowNumber = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (buffer[0] == '\n' || (strlen(buffer) > 2 && buffer[0] == '/' && buffer[1] == '/')) {
            continue;
        }
        targetNumber = 0;
        targetIndex = 0;

        int midNumber = 0;
        for(int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\n') {
                break;
            } else if (buffer[i] == ' ' || buffer[i] == '\t') {
                if (midNumber) {
                    for(int j = i; buffer[j] != '\0'; j++) {
                        if (buffer[j] == ',') {
                            break;
                        } else if (buffer[j] == ' ' || buffer[j] == '\t') {
                            continue;
                        } else {
                            fclose(file);
                            logMessage(logFile, ERROR, "Invalid character in pin file\n");
                            return -1;
                        }
                    }
                } else {
                    continue;
                }
            } else if (buffer[i] == ',') {
                if (!midNumber) {
                    fclose(file);
                    logMessage(logFile, ERROR, "Invalid character in pin file\n");
                    return -1;
                }

                targetIndex++;
                target[targetNumber][targetIndex] = '\0';

                targetNumber++;
                if (targetNumber > 2) {
                    fclose(file);
                    logMessage(logFile, ERROR, "Invalid character in pin file\n");
                    return -1;
                }

                midNumber = 0;
                targetIndex = 0;
            } else if (buffer[i] < '0' || buffer[i] > '9') {
                fclose(file);
                logMessage(logFile, ERROR, "Invalid character in pin file\n");
                return -1;
            } else {
                midNumber = 1;
                target[targetNumber][targetIndex] = buffer[i];
                targetIndex++;
            }
        }
        if (!midNumber) {
            fclose(file);
            logMessage(logFile, ERROR, "Invalid character in pin file\n");
            return -1;
        }

        int pinType = atoi(typeString);
        switch (pinType) {
            case 0:
            (*pins)[rowNumber].type = IN;
            break;
            case 1:
            (*pins)[rowNumber].type = OUT;
            break;
            default:
            fclose(file);
            logMessage(logFile, ERROR, "Invalid character in pin file\n");
            return -1;
        }
        (*pins)[rowNumber].number = atoi(numberString);

        // Check if the pin number is considered valid
        int valid = 0;
        for (int i = 0; i < NUM_VALID_PINS; i++) {
            if ((*pins)[rowNumber].number == VALID_PINS[i]) {
                valid = 1;
                break;
            }
        }
        if (!valid) {
            fclose(file);
            logMessage(logFile, ERROR, "Invalid pin number in pin file\n");
            return -1;
        }

        (*pins)[rowNumber].netNumber = atoi(netString);

        rowNumber++;

        memset(buffer, 0, sizeof(buffer));
        memset(typeString, 0, sizeof(typeString));
        memset(numberString, 0, sizeof(numberString));
        memset(netString, 0, sizeof(netString));
    }

    fclose(file);
    return 0;
}

int readNets(char *filename, net **nets, int *numRows, char *logFile, int debugMode) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        logMessage(logFile, ERROR, "Could not open net file\n");
        return -1;
    }

    *numRows = numberOfRows(file);
    *nets = malloc((*numRows) * sizeof(net));

    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    char netString[BUFFER_SIZE];
    char typeString[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    memset(netString, 0, sizeof(netString));
    memset(typeString, 0, sizeof(typeString));

    char *target[2];
    target[0] = netString;
    target[1] = typeString;
    int targetNumber = 0;
    int targetIndex = 0;

    int rowNumber = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (buffer[0] == '\n' || (strlen(buffer) > 2 && buffer[0] == '/' && buffer[1] == '/')) {
            continue;
        }
        targetNumber = 0;
        targetIndex = 0;

        int midNumber = 0;
        for(int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\n') {
                break;
            } else if (buffer[i] == ' ' || buffer[i] == '\t') {
                if (midNumber) {
                    for(int j = i; buffer[j] != '\0'; j++) {
                        if (buffer[j] == ',') {
                            break;
                        } else if (buffer[j] == ' ' || buffer[j] == '\t') {
                            continue;
                        } else {
                            fclose(file);
                            logMessage(logFile, ERROR, "Invalid character in net file\n");
                            return -1;
                        }
                    }
                } else {
                    continue;
                }
            } else if (buffer[i] == ',') {
                if (!midNumber) {
                    fclose(file);
                    logMessage(logFile, ERROR, "Invalid character in net file\n");
                    return -1;
                }

                targetIndex++;
                target[targetNumber][targetIndex] = '\0';

                targetNumber++;
                if (targetNumber > 1) {
                    fclose(file);
                    logMessage(logFile, ERROR, "Invalid character in net file\n");
                    return -1;
                }

                midNumber = 0;
                targetIndex = 0;
            } else if (buffer[i] < '0' || buffer[i] > '9') {
                fclose(file);
                logMessage(logFile, ERROR, "Invalid character in net file\n");
                return -1;
            } else {
                midNumber = 1;
                target[targetNumber][targetIndex] = buffer[i];
                targetIndex++;
            }
        }
        if (!midNumber) {
            fclose(file);
            logMessage(logFile, ERROR, "Invalid character in net file\n");
            return -1;
        }

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
            fclose(file);
            logMessage(logFile, ERROR, "Invalid character in net file\n");
            return -1;
        }
        (*nets)[rowNumber].number = atoi(netString);

        memset(buffer, 0, sizeof(buffer));
        memset(netString, 0, sizeof(netString));
        memset(typeString, 0, sizeof(typeString));

        rowNumber++;
    }

    fclose(file);
    return 0;
}

int initializeNets(net *nets, pin *pins, int numPins, int numNets, char *logFile, int debugMode) {
    for (int i = 0; i < numNets; i++) {
        nets[i].numPins = 0;
        nets[i].previousState = 0;
        nets[i].pins = NULL;
    }

    int netNumber, found;

    for (int i = 0; i < numPins; i++) {
        netNumber = pins[i].netNumber;
        found = 0;

        for (int j = 0; j < numNets; j++) {
            if (nets[j].number == netNumber) {
                found = 1;

                nets[j].numPins++;
                if (nets[j].numPins > 1) {
                    pin *temp = nets[j].pins;
                    nets[j].pins = malloc(nets[j].numPins * sizeof(pin));
                    for (int k = 0; k < nets[j].numPins - 1; k++) {
                        nets[j].pins[k] = temp[k];
                    }
                    free(temp);
                    nets[j].pins[nets[j].numPins - 1] = pins[i];
                } else {
                    nets[j].pins = malloc(nets[j].numPins * sizeof(pin));
                    nets[j].pins[0] = pins[i];
                }
            }
        }

        if (!found) {
            logMessage(logFile, ERROR, "Non-existent net used in pin file\n");
            return -1;
        }
    }

    return 0;
}

int initialize(char *pinFile, char *netFile, int *numPins, int *numNets, net **nets, char *logFile, int debugMode) {
    pin *pins;
    int pinStatus = readPins(pinFile, &pins, numPins, logFile, debugMode);
    int netStatus = readNets(netFile, nets, numNets, logFile, debugMode);
    int initStatus = initializeNets(*nets, pins, *numPins, *numNets, logFile, debugMode);

    if (pinStatus) {
        free(pins);
        return pinStatus;
    }

    if (netStatus) {
        free(pins);
        return netStatus;
    }

    if (initStatus) {
        free(pins);
        return initStatus;
    }

    for (int j = 0; j < *numPins; j++) {
        int status = initializePin(&(pins[j]), logFile, debugMode);
        if (status < 0) {
            free(pins);
            return -1;
        }
    }

    for (int i = 0; i < *numNets; i++) {
        if ((*nets)[i].numPins == 0) {
            free(pins);
            logMessage(logFile, ERROR, "Net with no pins detected\n");
            return -1;
        }

        for (int j = 0; j < (*nets)[i].numPins; i++) {
            int status = initializePin(&((*nets)[i].pins[j]), logFile, debugMode);
            if (status < 0) {
                free(pins);
                logMessage(logFile, ERROR, "Could not initialize pin\n");
                return -1;
            }
        }
    }

    free(pins);
    return 0;
}
#endif
