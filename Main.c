#include <stdio.h>

#include "FileRead.c"
#include "Pin.c"
#include "Net.c"
#include "Logging.c"

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: ./LogicSim pinFile netFile")
        return -1;
    }
    char *pinFile = argv[1];
    char *netFile = argv[2];
    char *logFile = argv[3];
    fclose(fopen(logFile, "w"));

    pin EXIT_PIN;
    EXIT_PIN.type = IN;
    EXIT_PIN.number = 11;
    EXIT_PIN.netNumber = -1;
    initializePin(&EXIT_PIN, logFile);

    net *nets;
    int numPins, numNets;

    // INITIALIZATION
    int status = initialize(pinFile, netFile, &numPins, &numNets, &nets, logFile);
    if (status) {
        // TODO: Switch on the status and log it
        printf("Error reading file\n");
        for (int i = 0; i < numNets; i++) {
            for (int j = 0; j < nets[i].numPins; j++) {
                uninitializePin(&(nets[i].pins[j]));
            }
            free(nets[i].pins);
        }
        free(nets);
        return -1;
    }

    // TODO: Move this to logging
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

    // RUNNING
    int done = 0;
    while (!done) {
        if (getPinState(&EXIT_PIN)) {
            done = 1;
        } else {
            for (int i = 0; i < numNets; i++) {
                int netOn = getNetState(&(nets[i]));
                if (netOn < 0) {
                    printf("Invalid Pin Type\n");
                    return -1;
                }
                // TODO: Add logging
                setNetOutput(&(nets[i]), netOn);
                nets[i].previousState = netOn;
            }
        }
    }

    // CLEANUP
    for (int i = 0; i < numNets; i++) {
        for (int j = 0; j < nets[i].numPins; j++) {
            uninitializePin(&(nets[i].pins[j]));
        }
        free(nets[i].pins);
    }
    free(nets);
    return  0;
}
