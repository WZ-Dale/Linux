/*************************************************************************
Describe: 线程等待--获取线程退出返回值，允许系统回收线程资源
int pthread_join(pthread_t thread, void **retval);
	thread：    要等待的线程id
	retval：    输出型参数-用于获取退出线程的返回值
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg)
{
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
    // pthread_cancel(tid);
    char *ptr = NULL;
    ret = pthread_join(tid, (void**)&ptr);
    if (ret == EINVAL) {
		  printf("this thread can not be wait!!\n");
    }
    printf("retval:%d\n", ret);
    return 0;
}
