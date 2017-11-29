#ifndef PIN_C_INCLUDE
#define PIN_C_INCLUDE

#include <stdlib.h>
#include <ugpio/ugpio.h>

#include "Pin.h"
#include "Logging.c"

int initializePin(pin *pinToInit, char *logFile, int debugMode) {
    if (debugMode) {
        char message[2048];
        sprintf(message, "Initializing pin: %d", pinToInit->number);
        logMessage(logFile, INFO, message);
    }
    int pinNumber = pinToInit->number;

    // Check if it's already exported
    int status = gpio_is_requested(pinNumber);

    // Export the pin
    if (!status) {
        status = gpio_request(pinNumber, NULL);
        if (status < 0) {
            return -1;
        }
    }

    // Set the pin type
    if (pinToInit->type == IN) {
        status = gpio_direction_input(pinNumber);
        if (status < 0) {
            return -1;
        }
    } else {
        status = gpio_direction_output(pinNumber, 0);
        if (status < 0) {
            return -1;
        }
    }
    return 0;
}

int uninitializePin(pin *pinToUninit, char *logFile, int debugMode) {
    int status = gpio_free(pinToUninit->number);
    if (status < 0) {
        logMessage(logFile, ERROR, "Failed to uninitialize pin");
        return -1;
    }
    return 0;
}

int getPinState(pin *pinToCheck, char *logFile, int debugMode) {
    if (pinToCheck->type != IN) {
        logMessage(logFile, ERROR, "Attempted to get state of output pin");
        return -1;
    }

    int pinState = gpio_get_value(pinToCheck->number);
    if (debugMode) {
        char message[2048];
        sprintf(message, "Pin number %d's state: %d", pinToCheck->number, pinState);
        logMessage(logFile, DEBUG , message);
    }
    return pinState;
}

int setPinState(pin *pinToSet, int state, char *logFile, int debugMode) {
    if (pinToSet->type != OUT) {
        logMessage(logFile, ERROR, "Attempted to set input pin");
        return -1;
    }

    gpio_set_value(pinToSet->number, state);
    if (debugMode) {
        char message[2048];
        sprintf(message, "Setting pin %d to %d", pinToSet->number, state);
        logMessage(logFile, DEBUG, message);
    }
    return 0;
}

#endif
