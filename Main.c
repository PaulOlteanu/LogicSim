#include <stdio.h>

#include "FileRead.c"
#include "Pin.c"
#include "Net.c"

int main(int argc, char * argv[]) {
    pin EXIT_PIN;
    EXIT_PIN.type = IN;
    EXIT_PIN.number = 11;
    EXIT_PIN.netNumber = -1;
    char *pinFile = "pinTest.csv";
    char *netFile = "netTest.csv";

    net *nets;
    int numPins, numNets;

    int status = initialize(pinFile, netFile, &numPins, &numNets, &nets);
    if (status) {
        printf("Error reading file\n");
        for (int i = 0; i < numNets; i++) {
            for (int j = 0; j < nets[i].numPins; j++) {
                uninitializePin(nets[i].pins[j]);
            }
            free(nets[i].pins);
        }
        free(nets);
        return -1;
    }

    for (int i = 0; i < numNets; i++) {
        printf("Net #%d:\n", nets[i].number);
        printf("Number of pins: %d\n", nets[i].numPins);
        printf("Net type: %d\n", nets[i].type);
        for (int j = 0; j < nets[i].numPins; j++) {
            printf("Pin Number: %d\n", nets[i].pins[j].number);
            printf("Pin Type: %d\n", nets[i].pins[j].type);
        }
        printf("\n");
    }

    while (1) {
        if (getPinState(EXIT_PIN)) {
            // Clear things
            return 0;
        }

        for (int i = 0; i < numNets; i++) {
            int netOn = getNetState(&(nets[i]));
            // TODO: Add logging
            setNetOutput(&(nets[i]), netOn);
            nets[i].previousState = netOn;
        }
    }

    for (int i = 0; i < numNets; i++) {
        for (int j = 0; j < nets[i].numPins; j++) {
            uninitializePin(nets[i].pins[j]);
        }
        free(nets[i].pins);
    }
    free(nets);
    return  0;
}
