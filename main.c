#include "dir.h"
#include "global.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void help() {
    printf("Cbuster is a GoBuster rewrite in C. There are the following methods:\n");
    printf("  help         Show this help message\n");
    printf("  dir          Directory mode\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        help();
        return 1;
    }
    
    GlobalOptions* globalOpts = loadGlobalOptions(argc - 1, argv + 1); 
    
    if (strcmp(argv[1], "help") == 0) {
        help();
    } else if (strcmp(argv[1], "dir") == 0) {
        dir(argc - 1, argv + 1, globalOpts);
    } else {
        printf("Unknown command: %s\n", argv[1]);
        help();
        return 1;
    }
    
    freeGlobalOptions(globalOpts);
    return 0;
}
