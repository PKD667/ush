#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "unistd.h"
#include "limits.h"

#include "../include/main.h"
#include "../include/utils.h"
#include <stddef.h>


#define READ_ERROR -6

#define MODE_INTERACTIVE 0
#define MODE_SCRIPT 1



int main(int argc, char *argv[]) {



    init();

    int mode = MODE_INTERACTIVE;
    FILE* STREAM = stdin;

    if (argc > 1) 
    {
        if (access(argv[1], F_OK) == 0) 
        {
            STREAM = fopen(argv[1], "r");
            mode = MODE_SCRIPT;
        }
        else 
        {
            printf("File '%s' does not exist\n", argv[1]);
            return 1;
        }
    }



    while (1) {

        if (mode == MODE_INTERACTIVE) {
            printf("%s", getenv("PS1"));
        }

        char* line = NULL;
        size_t len = 0;
        ssize_t read = readline(&line, STREAM);

        //printf("read: %zd\n", read);

        if (read == EOF) {
            break;
        }
        else if (read == READ_ERROR) {
            printf("error reading line\n");
            break;
        }
        else if (read == 0) {
            continue;
        }

        //printf("read: %zd ==> '%s'\n ", read, line);

        procline(&line);


        //Do stuff now
        ins instruction = {0};
        parseline(&line,&instruction);

        run(&instruction);

        free(line);
    }
    return 0;

}

ssize_t readline(char** line,FILE* stream) {
    *line = calloc(1024, 1);
    int i = 0;
    while(1) {
        char c = getc(stream);
        //printf("c: '%d'\n", c);
        if (c == '\n' || c == ';' || c == EOF || c == '\0') {
            if (i != 0) {
                return i;
            }
            else {
                if (c == EOF) {
                    return EOF;
                }
                return READ_ERROR;
            }
        }
        

        if (i >= 1024) {
            *line = realloc(line, 1024*2);
        }


        (*line)[i++] = c;
    }
}

int init()
{
    // set the default values
    setenv("PS1", "[ush]$ ", 1);
    setenv("PATH", "/bin:/usr/bin", 0);
    return 0;
}