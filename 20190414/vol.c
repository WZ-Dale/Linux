/*  volatile关键字
 *      保持内存可见性----每次操作变量都需要重新从内存中获取
 *      防止编译器过度优化
 * */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile int i = 1;
void sigcb(int signo)
{
    i= 0;
    printf("-------\n");
}
int main()
{
    signal(SIGINT, sigcb);
    while(i) {
    }
    return 0;
}
