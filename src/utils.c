#include "stdlib.h"
#include "string.h"

unsigned int splitm (char* string,char delim,char** dest,unsigned max)
{
    //msg(DBG3,"Splitting \"%s\" with delim '%c' and max %d",string,delim,max);
    char* token = strtok(string, &delim);
    unsigned int count = 0;
    while (token != NULL && count < max)
    {
        //msg(DBG3,"Token: %s",token);
        dest[count] = token;
        count++;
        token = strtok(NULL, &delim);
    }
    return count;
}