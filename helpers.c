#include "helpers.h"
#include <string.h>
#include <stdlib.h>

//add error handling
char** loadStringArray(const char *inputString) {
    char *input = strdup(inputString);
    char *token;
    char *delimiters = ";";
    char **strings = malloc(100 * sizeof(char*));
    int index = 0;

    token = strtok(input, delimiters);
    while (token != NULL && index < 100) {
        strings[index++] = strdup(token);
        token = strtok(NULL, delimiters);
    }
    strings[index] = NULL;

    free(input);
    return strings;
}

