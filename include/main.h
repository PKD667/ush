#include <stdio.h>
#define MAX_PATH 1024
#define MAX_ARGS 64


#define name(in) (in->argv[0])



typedef struct ins {
    char* line;
    char* argv[MAX_ARGS];
    int argc;
}ins;

int init();

int parseline(char** line, ins* instruction);
int run(ins* in);
int builtin(ins* in);

char* getpath(const char* name);
int cutline(char* line,char** args);
int procline(char** line);
ssize_t readline(char** line,FILE* stream);