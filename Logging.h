#ifndef LOGGING_H_INCLUDE
#define LOGGING_H_INCLUDE

typedef enum LEVEL {ERROR, INFO, DEBUG} LOG_LEVEL;

char *currentTimestamp();
int logMessage(const char *filename, LOG_LEVEL logLevel, const char* message);

#endif
