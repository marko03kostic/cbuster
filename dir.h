#ifndef DIR_H
#define DIR_H

#include "httpclient.h"
#include <stdbool.h>

typedef struct {
    bool addSlash;
    char **cookies;
    bool discoverBackup;
    int excludeLength;
    bool expanded;
    char *extension;
    bool followRedirect;
    bool headers;
    bool help;
    bool hideLength;
    httpMethod method;
    bool noStatus;
    bool noTLSValidation;
    char *password;
    char *proxy;
    bool randomAgent;
    bool retry;
    int retryAttempts;
    char *statusCodes;
    char *statusCodesBlacklist;
    int timeout;
    char *url;
    char *userAgent;
    char *username;
} DirOptions;

DirOptions* createDirOptions();

char** loadStringArray(const char *cookieString);

void dirHelp();

void dir(int argc, char *argv[]);

void freeDirOptions(DirOptions *opts);

#endif
