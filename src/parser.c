#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/utils.h"
#include "../include/main.h"




int parse(char* line, ins* instruction) {

    instruction->line = line;
    // get the string before the first ' '
    instruction->name = strtok(line, " ");
    // get the rest of the string
    char* args = strtok(NULL, "");
    // split the string by ' ' and put it in instruction->args
    instruction->argc = splitm(args, ' ', instruction->args, MAX_ARGS);
    // remove the last arg if its a whitespace or newline
    if (instruction->args[instruction->argc-1][0] == ' ' || instruction->args[instruction->argc-1][0] == '\n') {
        instruction->args[instruction->argc-1] = NULL;
        instruction->argc--;
    }
    
    /*
    printf("name: %s\n", instruction->name);
    //print args
    for (int i = 0; i < instruction->argc; i++) {
        printf("args[%d]: %s\n", i, instruction->args[i]);
    }
    */


    return 0;
}