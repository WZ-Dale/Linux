/*  匿名管道的基本使用
 *  #include <unistd.h>
 *  int pipe(int pipefd[2]);
 *      pipefd  输出型参数
 *      pipefd[0]   用于从管道读数据
 *      pipefd[1]   用于向管道写数据
 *  返回值：0   失败：-1
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret < 0) {
        perror("pipe error");
        return -1;
    }
    // 管道创建成功,接下来创建子进程
    int pid = fork();
    if (pid < 0) {
        perror("fork error");
        return -1;
    }else if (pid == 0) {
        // child write
        close(pipefd[1]);
        /*
        sleep(3);
        int total_len = 0;
        while(1) {
            char *ptr = "hello~~~";
            int ret = write(pipefd[1],  ptr, strlen(ptr));
            total_len += ret;
            printf("ret:%d\n", total_len);
        }
        */
    }else  {
        sleep(1);
        close(pipefd[1]);
        //parent read 
        char buf[1024] = {0};
        int ret = read(pipefd[0], buf, 1023);
        printf("read buf:[%d - %s]\n", ret, buf);
    }
    return 0;
}
