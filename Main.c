#include <stdio.h>

#include "CSVRead.c"

int main() {
    char *pinFile = "pinTest.csv";
    char *netFile = "netTest.csv";
    net *nets;
    int numPins, numNets;
    int status = initialize(pinFile, netFile, &numPins, &numNets, &nets);
    if (status) {
        printf("HERE\n");
        free(nets);
        return -1;
    }

    for (int i = 0; i < numNets; i++) {
        free(nets[i].pins);
    }
    free(nets);
    return  0;
}
