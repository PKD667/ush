#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "unistd.h"

#include "../include/main.h"
#include "../include/utils.h"

//char S_PATH[MAX_PATH*8];
char* PATH[64] = {"/bin", "/usr/bin", "/usr/local/bin", "/sbin", "/usr/sbin", "/usr/local/sbin", NULL};

char PWD[MAX_PATH];

char PS1[256] = ">"; // prompt string

int main(int argc, char *argv[]) {

// ...
// Dont worry about argc and argv for now :)
//
    while (1) {
        printf("%s", PS1);
        char* line = NULL;
        size_t len = 0;
        ssize_t read = getline(&line, &len, stdin);
        // we nned to remove the fucking newline
        if (read == -1) {
            printf("Error reading line\n");
            continue;
        }
        // check if the line is empty
        if (line[0] == '\n') {
            continue;
        }
        line[strlen(line)-1] = '\0';
        //printf("Read %zd bytes: %s", read, line);

        char* stats[64];
        int statcount = splitm(line, ';', stats, 64);

        for (int i = 0; i < statcount; i++) {
            //Do stuff now
            ins instruction = {0};
            parse(line,&instruction);

            run(&instruction);
        }

        free(line);
    }

}