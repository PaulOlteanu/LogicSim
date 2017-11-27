#ifndef PIN_C_INCLUDE
#define PIN_C_INCLUDE

#include <stdlib.h>
#include <ugpio/ugpio.h>

#include "Pin.h"

int initializePin(pin *pinToInit) {
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

int uninitializePin(pin *pinToUninit) {
    int status = gpio_free(pinToUninit->number);
    if (status < 0) {
        return -1;
    }
    return 0;
}

int getPinState(pin *pinToCheck) {
    if (pinToCheck->type != IN) {
        return -1;
    }

    return gpio_get_value(pinToCheck->number);
}

int setPinState(pin *pinToSet, int state) {
    if (pinToSet->type != OUT) {
        return -1;
    }

    gpio_set_value(pinToSet->number, state);
    return 0;
}

#endif
