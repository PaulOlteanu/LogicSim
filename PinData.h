#ifndef PINDATA_H_INCLUDE
#define PINDATA_H_INCLUDE

typedef enum PIN_TYPE {IN, OUT} PIN_TYPE;
typedef enum NET_TYPE {AND, OR, XOR, NAND} NET_TYPE;

typedef struct pin {
    int number; // 1-14
    PIN_TYPE type;
    int netNumber; // Any number
} pin;

typedef struct net {
    int number; // Any number
    NET_TYPE type;
    pin *pins;
    int numPins;
} net;

#endif
