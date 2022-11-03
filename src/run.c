#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int run(ins* in) {

    // check if the command is a builtin
    // ...
    if (builtin(in)) {
        return 0;
    }

    char* path = NULL;

    // check if the command is file that exists and is executable
    if (access(name(in),X_OK) == 0)
    {
        path = name(in);
    }
    else {
        // if not, check if the command is in PATH
        path = getpath(name(in));
        if (path == NULL) {
            printf("Command not found : %s\n", name(in));
            return 1;
        }
    }

    // if it is, run it
    int pid = fork();
    if (pid == 0) {
        // child
        // printf the finl command with args
        //printf("Running: '%s'", path);
        //for (int i = 1; i < in->argc; i++) {
        //    printf(" '%s'", in->argv[i]);
        //}
        //printf("\n");

        execv(path, in->argv);
        printf("Error running '%s'\n", name(in));
        exit(1);
    } else {
        // parent
        wait(NULL);
    }



    return 0;
}

