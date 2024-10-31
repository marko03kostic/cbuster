#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdbool.h>

typedef struct {
    int delayMs;
    bool noError;
    bool noProgress;
    char *output;
    char *pattern;
    bool quiet;
    int threads;
    bool verbose;
    char *wordlist;
} GlobalOptions;


GlobalOptions* loadGlobalOptions(int argc, char *argv[]);

GlobalOptions* createGlobalOptions();

void freeGlobalOptions(GlobalOptions *opts);

#endif

