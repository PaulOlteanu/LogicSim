#ifndef PIN_C_INCLUDE
#define PIN_C_INCLUDE

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

int pinState(pin *pinToCheck) {
    return 0;
    // return read(pinToCheck.number)
}
#endif
