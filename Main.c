#include <stdio.h>

#include "CSVRead.c"

int main() {
    char *filename = "pinTest.csv";
    pin *pins;
    int numPins = 1;
    int pinStatus = readPins(filename, &pins, &numPins);
    printf("Status: %d\n", pinStatus);
    printf("Rows: %d\n", numPins);
    printf("Pin Type: %d\n", pins[0].type);
    printf("Pin Type: %d\n", pins[1].type);
    free(pins);
    return  0;    
}
