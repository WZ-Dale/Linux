/*  fork初使用
 *      通过复制调用进程，创建一个新的进程（子进程）
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("parent pid:%d\n", getpid());
    int a = 100;
    //pid_t fork(void);
    pid_t pid = fork(); 
    if (pid < 0) {
        return -1;
    }else if (pid == 0){
        a = 20;
        printf("child!! pid:%d----a:%d--%p\n", getpid(), a, &a);
    }else {
        sleep(1);
        printf("parent!!:%d---child :%d----a:%d---%p\n", 
                getpid(), pid, a, &a);
    }
    printf("leihoua!! %d\n", a);

    return 0;
}
