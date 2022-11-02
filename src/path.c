#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <stdio.h>

#include "../include/main.h"
#include "../include/utils.h"


char* getpath(const char* name) {
    char* path_const = getenv("PATH");
    char* path_list[128];
    char path_str[strlen(path_const)];
    strcpy(path_str,path_const);
    int path_count = splitm(path_str, ':', path_list, 128);
    // check if the command is in PATH
    for (int i = 0;i < path_count; i++) {
        char* path = malloc(strlen(path_list[i]) + strlen(name) + 2);
        sprintf(path, "%s/%s", path_list[i], name);
        //printf("Checking '%s'\n", path);
        if (access(path, F_OK) == 0) {
            return path;
        }
    }
    return NULL;
}