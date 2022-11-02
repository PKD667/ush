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
void popcharn(char* s,long s_size,int pos)
{
    memmove(&s[pos], &s[pos + 1], s_size - pos);
}


// the code below is magic fuckery, don't touch it
// MADE BY Copilot™
int replace(char** str,char* old,char* rep)
{
    // replace old with rep in str
    char* new = malloc(strlen(*str) + 1);
    strcpy(new,*str);
    int count = 0;
    char* p = strstr(new,old);
    while (p != NULL)
    {
        count++;
        p = strstr(p+1,old);
    }
    if (count == 0)
    {
        return 0;
    }
    int new_size = strlen(new) + (strlen(rep) - strlen(old)) * count + 1;
    char* new2 = malloc(new_size);
    strcpy(new2,new);
    p = strstr(new2,old);
    while (p != NULL)
    {
        memmove(p+strlen(rep),p+strlen(old),strlen(p+strlen(old))+1);
        memcpy(p,rep,strlen(rep));
        p = strstr(p+1,old);
    }
    free(new);
    *str = new2;
    return 1;
}