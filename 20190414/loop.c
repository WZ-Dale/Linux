#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("-------\n");
}
int main()
{
    //int kill(pid_t pid, int sig);
    //给指定进程发送指定信号
    //kill(getpid(), SIGSEGV);
    
    //int raise(int sig);
    //给调用进程/线程发送指定信号
    //raise(SIGQUIT);

    //void abort(void);
    //给调用进程发送SIGABRT
    //abort();
    
    //unsigned int alarm(unsigned int seconds);
    //seconds秒之后给调用进程发送SIGALRM信号
    //seconds==0表示取消定时器
    //返回值上一个定时器剩余的时间或0
    //int ret = alarm(3);
    //sleep(1);
    //ret = alarm(0);
    signal(SIGINT, sigcb);
    while(1) {
        printf("hello ~~ \n" );
        sleep(10);
    }
    return 0;
}
