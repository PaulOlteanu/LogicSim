#ifndef NET_C_INCLUDE
#define NET_C_INCLUDE

#include "Pin.c"

typedef enum NET_TYPE {AND, OR, XOR, NAND} NET_TYPE;
typedef struct net {
    int number; // Any number
    NET_TYPE type;
    pin *pins;
    int numPins;
    int previousState;
} net;

int getNetState(net *netToSim) {
    switch (netToSim->type) {
        case AND:
        // If any are off, return false
        for (int i = 0; i < netToSim->numPins; i++) {
            if (netToSim->pins[i].type == IN) {
                if (getPinState(&(netToSim->pins[i])) == 0) {
                    return 0;
                }
            } else {
                continue;
            }
        }
        return 1;

        case OR:
        // If any are on, return true
        for (int i = 0; i < netToSim->numPins; i++) {
            if (netToSim->pins[i].type == IN) {
                if (getPinState(&(netToSim->pins[i])) == 1) {
                    return 1;
                }
            } else {
                continue;
            }
        }
        return 0;

        case XOR:; // Semicolon is intentional
        int out = 0;
        // Continually xor all the pins
        // Will be on if there's an odd number of pins
        for (int i = 0; i < netToSim->numPins; i++) {
            if (netToSim->pins[i].type == IN) {
                out ^= getPinState(&(netToSim->pins[i]));
            } else {
                continue;
            }
        }
        return out;

        case NAND:
        // If any are off, return true
        for (int i = 0; i < netToSim->numPins; i++) {
            if (netToSim->pins[i].type == IN) {
                if (getPinState(&(netToSim->pins[i])) == 0) {
                    return 1;
                }
            } else {
                continue;
            }
        }
        return 0;

        default:
        return -1;
    }

    return -1;
}

int setNetOutput(net *netToSet, int state) {
    for (int i = 0; i < netToSet->numPins; i++) {
        if (netToSet->pins[i].type == OUT) {
            int status = setPinState(&(netToSet->pins[i]), state);
            if (status < 0) {
                return -1;
            }
        }
    }

    return 0;
}

#endif
