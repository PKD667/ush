#define MAX_PATH 1024
#define MAX_ARGS 64


extern char* PATH[64];
extern char PWD[MAX_PATH];

typedef struct ins {
    char* line;
    char* name;
    char* args[MAX_ARGS];
    int argc;
}ins;

int parse(char* line, ins* instruction);
int run(ins* in);

char* getpath(const char* name);;