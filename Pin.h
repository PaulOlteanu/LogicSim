#ifndef PIN_H_INCLUDE
#define PIN_H_INCLUDE

typedef enum PIN_TYPE {IN, OUT} PIN_TYPE;
const int NUM_VALID_PINS = 10;
const int VALID_PINS[] = {0, 1, 2, 3, 4, 5, 18, 19, 46, 11};

typedef struct pin {
    int number; // Must be one of the "valid pins"
    PIN_TYPE type;
    int netNumber; // Any number
} pin;

int initializePin(pin *pinToInit);
int uninitializePin(pin *pinToUninit);
int getPinState(pin *pinToCheck);
int setPinState(pin *pinToSet, int state);

#endif
