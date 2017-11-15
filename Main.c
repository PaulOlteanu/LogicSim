#include <stdio.h>

#include "CSVRead.c"

int main() {
    char *filename = "test.csv";
    pinRow *pinData;
    int numPins = 1;
    int status = readPins(filename, &pinData, &numPins);
    printf("Status: %d\n", status);
    printf("Rows: %d\n", numPins);
    printf("Pin Type: %d\n", pinData[0].type);
    return  0;    
}
