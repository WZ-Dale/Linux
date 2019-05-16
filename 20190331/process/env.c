/*获取环境变量的demo*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[])
{
    int i;
    //for (i = 0; env[i] != NULL; i++) {
    //    printf("env[%d] = [%s]\n", i, env[i]);
    //}
    //extern char **environ;
    //for (i = 0; environ[i] != NULL; i++) {
    //    printf("env[%d] = [%s]\n", i, environ[i]);
    //}
    //char *getenv(const char *name);
    for(i = 0; i < argc; i++) {
        printf("argv[%d]=[%s]\n", i, argv[i]);
    }
    extern char **environ;
    for (i = 0; environ[i] != NULL; i++) {
        printf("env[%d] = [%s]\n", i, environ[i]);
    }
    char *ptr = getenv("MYENV");
    printf("MYENV:[%s]\n", ptr);

    return 0;
}
