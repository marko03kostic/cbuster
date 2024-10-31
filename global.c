#include "global.h"
#include "helpers.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>

GlobalOptions* loadGlobalOptions(int argc, char *argv[]) {
    GlobalOptions* opts = createGlobalOptions();
    int c;

    while ((c = getopt(argc, argv, "zo:p:qt:vw:")) != -1) {
        switch (c) {
            case 'z':
                opts->noProgress = true;
                break;
            case 'o':
                opts->output = optarg;
                break;
            case 'p':
                opts->pattern = optarg;
                break;
            case 'q':
                opts->quiet = true;
                break;
            case 't':
                //sus
                opts->threads = atoi(optarg);
                break;
            case 'v':
                opts->noProgress = true;
                break;
            case 'w':
                opts->noProgress = true;
                break;
            case '?':
                break;
        }
    }

    for (int index = optind; index < argc; index++) {
        printf("Non-option argument: %s\n", argv[index]);
    }

    return opts;
}

GlobalOptions* createGlobalOptions() {
    GlobalOptions *opts = malloc(sizeof(GlobalOptions));
    
    if (opts == NULL) {
        fprintf(stderr, "Failed to allocate memory for GlobalOptions.\n");
        exit(EXIT_FAILURE);
    }
    
    opts->delayMs = 0;
    opts->noError = false;
    opts->noProgress = false;
    opts->output = NULL;
    opts->pattern = NULL;
    opts->quiet = false;
    opts->threads = 10;
    opts->verbose = false;
    opts->wordlist = NULL;

    return opts;
}

void freeGlobalOptions(GlobalOptions* globalOptions) {
    if (!globalOptions) {
        return;
    }

    free(globalOptions->output);
    free(globalOptions->pattern);
    free(globalOptions->wordlist);
    
    free(globalOptions);
}
