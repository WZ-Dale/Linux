#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("hello bit!!\n");
    //execl("./env", "env", "-l", NULL);// 无p,需要制定路径
    //execlp("ls", "ls", "-l", NULL);// 有p,无需指定路径
    char *env[32];
    env[0] = "MYENV=10000";
    env[1] = NULL;
    extern char **environ;
    execle("./env", "env", "-l", NULL, environ);// 有e,环境变量由用户设定
    printf("leihoua~~bite!!\n");// 进程已被替换,无法打印出此句
    return 0;
}
