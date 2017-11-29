#ifndef FILEREAD_H_INCLUDE
#define FILEREAD_H_INCLUDE

#include "Pin.h"
#include "Net.h"

int numberOfRows(FILE *file);
int readPins(char *filename, pin **pins, int *numRows, char *logFile, int debugMode);
int readNets(char *filename, net **nets, int *numRows, char *logFile, int debugMode);
int initializeNets(net *nets, pin *pins, int numPins, int numNets, char *logFile, int debugMode);
int initialize(char *pinFile, char *netFile, int *numPins, int *numNets, net **nets, char *logFile, int debugMode);

#endif
