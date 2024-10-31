#include "dir.h"
#include "global.h"
#include "httpclient.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

DirOptions* createDirOptions() {
    DirOptions *opts = malloc(sizeof(DirOptions));
    
    if (opts == NULL) {
        return NULL;
    }

    opts->addSlash = false;
    opts->cookies = NULL;
    opts->discoverBackup = false;
    opts->excludeLength = 0;
    opts->expanded = false;
    opts->extension = NULL;
    opts->followRedirect = false;
    opts->headers = NULL;
    opts->help = false;
    opts->hideLength = false;
    opts->method = HTTP_UNKNOWN;
    opts->noStatus = false;
    opts->noTLSValidation = true;
    opts->password = NULL;
    opts->proxy = NULL;
    opts->randomAgent = true;
    opts->retry = false;
    opts->retryAttempts = 3;
    opts->statusCodes = NULL;
    opts->statusCodesBlacklist = NULL;
    opts->timeout = 30;
    opts->url = NULL;
    opts->userAgent = NULL;
    opts->username = NULL;
    return opts;
}

DirOptions* loadDirOptions(int argc, char *argv[]) {
    DirOptions* dirOpts = createDirOptions();
    int c;
    
    while ((c = getopt(argc, argv, "fc:dex:rH:hm:nkP:s:b:u:a:U:")) != -1) {
        switch (c) {
            case 'f':
                dirOpts->addSlash = true;
                break;
            case 'c':
                dirOpts->cookies = loadStringArray(optarg);
                break;
            case 'd':
                dirOpts->discoverBackup = true;
                break;
            case 'e':
                dirOpts->expanded = true;
                break;
            case 'x':
                dirOpts->extension = optarg;
                break;
            case 'r':
                dirOpts->followRedirect = true;
                break;
            case 'H':
                dirOpts->headers = loadStringArray(optarg);
                break;
            case 'h':
                dirHelp();
                freeDirOptions(dirOpts);
                exit(EXIT_SUCCESS);
            case 'm':
                dirOpts->method = loadHttpMethod(optarg);
                break;
            case 'n':
                dirOpts->noStatus = true;
                break;
            case 'k':
                dirOpts->noTLSValidation = true;
                break;
            case 'P':
                dirOpts->password = optarg;
                break;
            case 's':
                dirOpts->statusCodes = optarg;
                break;
            case 'b':
                dirOpts->statusCodesBlacklist = optarg; 
                break;
            case 'u':
                dirOpts->url = optarg;
                break;
            case 'a':
                dirOpts->userAgent = optarg;
                break;
            case 'U':
                dirOpts->username = optarg;
                break;
            case '?':
                printf("unknown option\n");
                freeDirOptions(dirOpts);
                exit(EXIT_FAILURE);
        }
    }

    if (!dirOpts->url) {
        fprintf(stderr, "Error: Missing required argument -u (URL)\n");
        freeDirOptions(dirOpts);
        exit(EXIT_FAILURE);
    }

    for (int index = optind; index < argc; index++) {
        printf("Non-option argument: %s\n", argv[index]);
    }

    return dirOpts;
}

void freeDirOptions(DirOptions* dirOpts) {
    if (!dirOpts) {
        return;
    }

    free(dirOpts->cookies);
    free(dirOpts->extension);
    free(dirOpts->password);
    free(dirOpts->proxy);
    free(dirOpts->statusCodes);
    free(dirOpts->statusCodesBlacklist);
    free(dirOpts->url);
    free(dirOpts->userAgent);
    free(dirOpts->username);
    
    free(dirOpts);

}

void dirHelp() {
    printf("help");
}

void dir(int argc, char *argv[], GlobalOptions* globalOpts) {
    DirOptions* dirOpts = loadDirOptions(argc, argv);
    
    httpRequestOptions* httpOpts = loadHttpRequestOptions(dirOpts->userAgent,
            dirOpts->username,
            dirOpts->headers,
            dirOpts->cookies,
            dirOpts->method,
            dirOpts->url);

    freeDirOptions(dirOpts);
}


