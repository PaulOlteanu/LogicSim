#ifndef PIN_C_INCLUDE
#define PIN_C_INCLUDE

#include "Net.c"

typedef enum PIN_TYPE {IN, OUT} PIN_TYPE;
const int NUM_VALID_PINS = 14;
const int VALID_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 18, 19, 45, 46};

typedef struct pin {
    int number; // Must be one of the "valid pins"
    PIN_TYPE type;
    int netNumber; // Any number
} pin;

int getPinStateFromPinNumber(int pinNumber) {
    return 1;
}

int getPinState(pin *pinToCheck) {
    return 0;
    // return read(pinToCheck.number)
}
#endif
