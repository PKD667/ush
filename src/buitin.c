#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "../include/main.h"
#include "../include/utils.h"
#include <unistd.h>

int builtin(ins* in)
{
    /* 
        THE CODE BELOW IS REALLY STUPID 
        
        TODO:
         - Optimise it using a hash table with function pointers
    */
    if (strcmp(name(in), "cd") == 0) {
        chdir (in->argv[1]);
        return 1;
    }
    else if (strcmp(name(in), "exit") == 0) {
        exit(0);
    }
    else if (strcmp(name(in), "pwd") == 0) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return 1;
    }
    else if (strcmp(name(in), "export") == 0) {
        char* name = strtok(in->argv[1], "=");
        char* value = strtok(NULL, "=");
        setenv(name, value, 1);
        return 1;
    }
    else if (strcmp(name(in), "unset") == 0) {
        unsetenv(in->argv[1]);
        return 1;
    }
    else if (strcmp(name(in), "replace") == 0) {
        if (in->argc < 4) {
            printf("replace: too few arguments\n");
            return 1;
        }
        char* out = in->argv[1];
        replace(&out, in->argv[2], in->argv[3]);
        printf("%s\n", out);
        return 1;
    }
    else if (strcmp(name(in), "help") == 0) {
        printf("cd - change directory\n");
        printf("exit - exit the shell\n");
        printf("pwd - print working directory\n");
        printf("export - export a variable\n");
        printf("unset - unset a variable\n");
        printf("echo - print a message\n");
        printf("help - print this message\n");
        return 1;
    }

    else {
        return 0;
    }

}