/*进程终止方式demo*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
    int pid = fork();
    if (pid < 0) {
        perror("fork error");
        printf("fork error :%s\n", strerror(errno));
    }
    int i = 0;
    for (; i < 256; i++) {
        printf("error:[%s]\n", strerror(i));
    }
    printf("hello bit");// 此处没有'\n',则不会刷新缓冲区,即不会打印
    sleep(1);
    _exit(255);
}
