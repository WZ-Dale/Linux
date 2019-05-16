/*vfork基本认识*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = vfork();
    if (pid == 0) {
        //child
        printf("----child!! pid:[%d]\n", getpid());
    } else {
        printf("parent----- pid:[%d]\n", getpid());
    }
    return 0;
}
