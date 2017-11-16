#include <stdio.h>

#include "CSVRead.c"

int main() {
    char *pinFile = "pinTest.csv";
    char *netFile = "netTest.csv";
    pin *pins;
    net *nets;
    int numPins, numNets;
    int pinStatus = readPins(pinFile, &pins, &numPins);
    int netStatus = readNets(netFile, &nets, &numNets);
    if (pinStatus || netStatus) {
        free(pins);
        free(nets);
        return -1;
    }
    int initStatus = initNets(nets, pins, numPins, numNets);
    if (initStatus) {
        printf("HERE\n");
        free(pins);
        free(nets);
        return -1;
    }
    free(pins);
    for (int i = 0; i < numNets; i++) {
        free(nets[i].pins);
    }
    free(nets);
    return  0;    
}
