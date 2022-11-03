#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/utils.h"
#include "../include/main.h"



int parseline(char** line, ins* instruction) {



    instruction->line = *line;
    instruction->argc = cutline(*line, instruction->argv);
    // print all args

    //procargs(instruction->argc,instruction->argv);


    return 0;
}

int cutline(char* line,char** args) {
    int argc = 0;
    //printf("setting %d to %s\n", argc, line);
    args[argc++] = line;
    int l_size = strlen(line);
    for (int i = 0; i < l_size; i++) {
        //printf("char: %c\n", line[i]);
        if (line[i] == '"') {
            //printf("removing line[%d] - %c\n", i, line[i]);
            popcharn(line,l_size,i);
            do {
                i++;
            }
            while (line[i] != '"');
            //printf("removing line[%d] - %c\n", i, line[i]);
            popcharn(line,l_size,i);
        }
        else if (line[i] == ' ') {
            do 
            {
                line[i] = '\0';
                i++;
            } while (line[i] == ' ');
            if (line[i] != '\0') {
                //printf("putting args[%d] to '%c'\n ", argc, line[i]);
                args[argc++] = line+i;
                i--;
            }
  
        }
    }
    return argc;
}

int procline(char** line) {

    // env variables
    if (strchr((*line), '$') != NULL) {
        char* index = strchr(*line, '$');
        char* key = calloc(strlen(index),sizeof(char));
        // The key so the string from $ to the next space or \0
        int i = 0;
        while (index[i] != ' ' && index[i] != '\0') {
            key[i] = index[i];
            i++;
        }
        // get env var name
        char* var = getenv(key+1);
        if (var == NULL) {
            var = "";
        }
        free(key);

        *index = '\0';
        char* new_line = calloc(strlen(*line) + strlen(var) + 1, sizeof(char));
        sprintf(new_line, "%s%s", *line, var);
        //printf("new line: %s\n", new_line);

        free(*line);
        *line = new_line;
    }

    // pipes
    if (strchr((*line), '|') != NULL) {
        char* index = strchr(*line, '|');
        char* key = calloc(strlen(index),sizeof(char));
        // The key so the string from $ to the next space or \0
        int i = 0;
        while (index[i] != ' ' && index[i] != '\0') {
            key[i] = index[i];
            i++;
        }
        // get env var name
        char* var = getenv(key+1);
        if (var == NULL) {
            var = "";
        }
        free(key);

        *index = '\0';
        char* new_line = calloc(strlen(*line) + strlen(var) + 1, sizeof(char));
        sprintf(new_line, "%s%s", *line, var);
        //printf("new line: %s\n", new_line);

        free(*line);
        *line = new_line;
    }


    return 0;
}





