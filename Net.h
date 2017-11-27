#ifndef NET_H_INCLUDE
#define NET_H_INCLUDE

#include "Pin.h"

typedef enum NET_TYPE {AND, OR, XOR, NAND} NET_TYPE;

typedef struct net {
    int number; // Any number
    NET_TYPE type;
    struct pin *pins;
    int numPins;
    int previousState;
} net;

int getNetState(net *netToSim);
int setNetOutput(net *netToSet, int state);

#endif
