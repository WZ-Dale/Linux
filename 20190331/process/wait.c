/*进程等待-避免产生僵尸进程demo*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(-1);
    }else if (pid == 0) {
        sleep(5);
        exit(255);
    }
    //pid_t wait(int *status);
    //  等待任意一个子进程退出
    //  status：用于退出返回值
    //  返回值：返回退出子进程的pid； 出错:-1
    int status;
    //wait(&status);
    //pid_t waitpid(pid_t pid, int *status, int options);
    //  pid:    指定的进程id
    //          -1  等待任意子进程
    //          >0  等待指定子进程
    //  status：    用于获取返回值
    //  options：选项
    //          WNOHANG     将waitpid设置为非阻塞
    //  返回值：<0:出错     ==0:没有子进程退出   >0: 退出子进程的pid
    while (waitpid(pid, &status, WNOHANG) == 0) {
        printf("no exit~~~smoking~~\n");
        sleep(1);
    }
    //低7位为0则正常退出
    if (!(status & 0x7f))  {
        printf("child exit code:%d\n", (status >> 8) & 0xff);
    }
    if (WIFEXITED(status)) {
        printf("child exit code:%d\n", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
        printf("exit signal:%d\n", WTERMSIG(status));
    }

    while(1) {
        printf("打麻将~~~\n");
        sleep(1);
    }
    return 0;
}
