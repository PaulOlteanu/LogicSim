#ifndef NET_C_INCLUDE
#define NET_C_INCLUDE

#include "Pin.c"

typedef enum NET_TYPE {AND, OR, XOR, NAND} NET_TYPE;
typedef struct net {
    int number; // Any number
    NET_TYPE type;
    pin *pins;
    int numPins;
} net;

int simulateNet(net *netToSim) {
    switch (netToSim->type) {
        case AND:
            // If any are off, return false
            for (int i = 0; i < netToSim->numPins; i++) {
                if (pinState(&(netToSim->pins[i])) == 0) {
                    return 0;
                }
            }
            return 1;
            break;
        case OR:
            // If any are on, return true
            for (int i = 0; i < netToSim->numPins; i++) {
                if (pinState(&(netToSim->pins[i])) == 1) {
                    return 1;
                }
            }
            return 0;
            break;
        case XOR:; // Semicolon is intentional
            int out = 0;
            // Continually xor all the pins
            // Will be on if there's an odd number of pins
            for (int i = 0; i < netToSim->numPins; i++) {
                out ^= pinState(&(netToSim->pins[i]));
            }
            return out;
            break;
        case NAND:
            // If any are off, return true
            for (int i = 0; i < netToSim->numPins; i++) {
                if (pinState(&(netToSim->pins[i])) == 0) {
                    return 1;
                }
            }
            return 0;
            break;
        default:
            return -1;
    }
    return 0;
}

#endif
