#include <stdio.h>

#include "CSVRead.c"
#include "PinData.h"

int main() {
    char *pinFile = "pinTest.csv";
    char *netFile = "netTest.csv";
    net *nets;
    int numPins, numNets;
    int status = initialize(pinFile, netFile, &numPins, &numNets, &nets);
    if (status) {
        printf("Error reading file\n");
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

    for (int i = 0; i < numNets; i++) {
        free(nets[i].pins);
    }
    free(nets);
    return  0;
}
