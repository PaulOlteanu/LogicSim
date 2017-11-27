#ifndef FILEREAD_H_INCLUDE
#define FILEREAD_H_INCLUDE

#include "Pin.h"
#include "Net.h"

int numberOfRows(FILE *file);
int readPins(char *filename, pin **pins, int *numRows);
int readNets(char *filename, net **nets, int *numRows);
int initializeNets(net *nets, pin *pins, int numPins, int numNets);
int initialize(char *pinFile, char *netFile, int *numPins, int *numNets, net **nets);

#endif
