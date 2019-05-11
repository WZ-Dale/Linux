/*匿名管道实现命令连接
 * 将一个命令的输出结果作为下一个命令的输入进行处理
 * ps -ef
 *      输出：所有的进程信息--写入标准输出
 * grep ssh
 *      从标准输入读取数据，进行过滤处理
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret < 0) {
        perror("pipe error");
        return -1;
    }
    int pid1 = fork();
    if (pid1 == 0) {
        // child1 ps -ef
        close(pipefd[0]);// 把读端关闭
        dup2(pipefd[1], 1);// 将标准输出重定向到管道的写入端
        execlp("ps", "ps", "-ef", NULL);
    }
    int pid2 = fork();
    if (pid2 == 0) {
        // child2 grep ssh
        close(pipefd[1]);// 把写端关闭
        dup2(pipefd[0], 0);// 将标准输入重定向到管道的读取端
        execlp("grep", "grep", "ssh", NULL);
    }
    close(pipefd[0]);// 父进程的读端也需要关闭
    close(pipefd[1]);// 父进程的写端也需要关闭
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
