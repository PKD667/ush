#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/utils.h"
#include "../include/main.h"



int parse(char* line, ins* instruction) {

    instruction->line = line;
    instruction->argc = cutline(line, instruction->argv);
    // remove the last arg if its a whitespace or newline
    if (instruction->argv[instruction->argc-1][0] == ' ' || instruction->argv[instruction->argc-1][0] == '\n') {
        instruction->argv[instruction->argc-1] = NULL;
        instruction->argc--;
    }
    
    /*
    printf("name: %s\n", instruction->name);
    //print args
    for (int i = 0; i < instruction->argc; i++) {
        printf("args[%d]: %s\n", i, instruction->args[i]);
    }
    */

    //procargs(instruction->argc,instruction->argv);


    return 0;
}

int cutline(char* line,char** args) {
    int argc = 0;
    //printf("setting %d to %s\n", argc, line);
    args[argc++] = line;
    int l_size = strlen(line);
    for (int i = 0; i < l_size; i++) {
        if (line[i] == '"') {
            //printf("removing line[%d] - %c\n", i, line[i]);
            popcharn(line,l_size,i);
            do {
                i++;
            }
            while (line[i] != '"');
            popcharn(line,l_size,i);
        }
        else if (line[i] == ' ') {
            do 
            {
                line[i] = '\0';
                i++;
            } while (line[i] == ' ');
            i--;
            //printf("putting args[%d] to '%c'\n ", argc, line[i+1]);
            args[argc++] = line+i+1;
        }
    }
    return argc;
}

int procline(char** line) {

    for (int i = 0; i < strlen(*line); i++) {
        if (strchr(line[i], '$') != NULL) {
            //printf("Found a $ in %s\n", argv[i]);
            char* var = strchr(line[i], '$');
            var++;
            //printf("var is %s\n", var);
            char* val = getenv(var);
            //printf("val is %s\n", val);
            if (val == NULL) {
                val = "";
            }
            //printf("val is %s\n", val);
            char* newarg = calloc(strlen(line[i]) + strlen(val) + 1, sizeof(char));
            //printf("newarg is %s\n", newarg);
            strcpy(newarg, line[i]);
            //printf("newarg is %s\n", newarg);
            char* varpos = strstr(newarg, var);
            //printf("varpos is %s\n", varpos);
            strcpy(varpos-1, val);
            //printf("newarg is %s\n", newarg);
            line[i] = newarg;

        }
    }

    return 0;
}





