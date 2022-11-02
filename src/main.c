#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "unistd.h"
#include "limits.h"

#include "../include/main.h"
#include "../include/utils.h"







int main(int argc, char *argv[]) {
    init();
    while (1) {

        printf("%s", getenv("PS1"));
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

int init()
{
    // set the default values
    setenv("PS1", "[ush]$ ", 1);
    setenv("PATH", "/bin:/usr/bin", 0);
    return 0;
}