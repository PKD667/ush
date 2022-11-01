#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int run(ins* in) {

    // check if the command is a builtin
    // ...

    char* path = NULL;

    // check if the command is file that exists and is executable
    if (access(in->name,X_OK) == 0)
    {
        path = in->name;
    }
    else {
        // if not, check if the command is in PATH
        path = getpath(in->name);
        if (path == NULL) {
            printf("Command not found : %s\n", in->name);
            return 1;
        }
    }

    //convert args
    int e_argc = in->argc + 2;
    char** e_argv = calloc(e_argc,sizeof(char*));
    e_argv[0] = in->name;
    for (int i = 1; i < e_argc; i++) {
        e_argv[i] = in->args[i-1];
    }

    

    // if it is, run it
    int pid = fork();
    if (pid == 0) {
        // child
        execv(path, e_argv);
        printf("Error running '%s'\n", in->name);
        exit(1);
    } else {
        // parent
        wait(NULL);
    }



    return 0;
}

