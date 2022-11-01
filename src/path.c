#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <stdio.h>

#include "../include/main.h"


char* getpath(const char* name) {
    // check if the command is in PATH
    for (int i = 0;PATH[i] != NULL; i++) {
        if (PATH[i] == NULL) {
            break;
        }
        char* path = malloc(strlen(PATH[i]) + strlen(name) + 2);
        sprintf(path, "%s/%s", PATH[i], name);
        //printf("Checking '%s'\n", path);
        if (access(path, F_OK) == 0) {
            return path;
        }
    }
    return NULL;
}