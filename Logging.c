#ifndef LOGGING_C_INCLUDE
#define LOGGING_C_INCLUDE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef enum LEVEL {DEBUG, INFO, ERROR} LOG_LEVEL;

char *currentTimestamp() {
    time_t ltime;
    ltime = time(NULL);
    char *timeString = asctime(localtime(&ltime));
    timeString[strlen(timeString) - 1] = 0;
    return timeString;
}

int logMessage(const char *filename, LOG_LEVEL logLevel, const char* message) {
    FILE *infile;
    infile = fopen(filename,"a");
    if (!infile) {
        return -1;
    }
    switch (logLevel) {
        case DEBUG:
        fprintf(infile, "%-7s | %s | %s\n", "DEBUG", currentTimestamp(), message);
        break;
        case INFO:
        fprintf(infile, "%-7s | %s | %s\n", "INFO", currentTimestamp(), message);
        break;
        case ERROR:
        fprintf(infile, "%-7s | %s | %s\n", "ERROR", currentTimestamp(), message);
        break;
        default:
        return -1;
    }

    fclose(infile);
    return 0;
}

#endif
