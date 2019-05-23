/*************************************************************************
int pthread_detach(pthread_t thread);
  pthread_detach(tid);      分离一个指定线程,自己也可以
  线程的分离对于一个线程来说,任意线程在任意位置调用都可以
*************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg)
{
    // pthread_detach(pthread_self());
    sleep(3);
}
int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
		  printf("thread  create error\n");
		return -1;
    }
    pthread_detach(tid);
    // pthread_cancel(tid);
    char *ptr = NULL;
    ret = pthread_join(tid, (void**)&ptr);
    if (ret == EINVAL) {
		  printf("this thread can not be wait!!\n");
    }
    printf("retval:%d\n", ret);
    return 0;
}
