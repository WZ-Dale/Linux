/*************************************************************************
Describe: 实现条件变量的基本使用
    吃面---前提有人做面
    如果没有现成的面，等待老板做出来
    老板做出来面，就要唤醒顾客

    老板不会做太多的面---老板只会提前做一碗面
    如果已经有面做出来，但是没人吃，不会再做（等待）
    顾客吃碗面之后，老板再来一碗（唤醒老板 的等待）
	
未写完>>>待续>>>互斥锁和条件变量还有需要注意的地方
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int have_noodle = 1;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond;// 定义一个条件变量
pthread_mutex_t mutex;// 定义一个互斥锁
void *thr_boss(void * arg) 
{
  while(1) {
    pthread_mutex_lock(&mutex);
    //若面没有卖出去，则等待
    if (have_noodle == 1) {
      //等待
      //int pthread_cond_timedwait(pthread_cond_t *cond,
      //	    pthread_mutex_t *mutex,
      //	    struct timespec *abstime);
      //	cond:	条件变量
      //	mutex：	互斥锁
      //	abstime：   限时等待时长
      //	限时进行等待，超时后则返回
      //pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);
      //死等
      //pthread_cond_wait 中集合了解锁后挂起的操作（原子操作）
      //有可能还没来得及挂起就已经有人唤醒--白唤醒--导致死等
      pthread_cond_wait(&cond, &mutex);
    }
    //面被人买了，要再做一碗
    printf("noodle~~~+1\n");
    have_noodle += 1;
    //面做出来了~唤醒顾客
    //int pthread_cond_broadcast(pthread_cond_t *cond);
    //  广播唤醒----唤醒所有等待的人
    //int pthread_cond_signal(pthread_cond_t *cond);
    //  唤醒至少一个等待的人
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
void *thr_customer(void *arg) 
{
  while(1) {
    pthread_mutex_lock(&mutex);
    //若没有现成的面，等老板做好
    if (have_noodle == 0) {
      //等待
      pthread_cond_wait(&cond, &mutex);
    }
    //有面了就可以吃了
    printf("noodle~~delicious\n");
    have_noodle -= 1;
    //吃完面,再来一碗--唤醒老板
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t tid1, tid2;
  int ret;
  //条件变量 初始化
  //int pthread_cond_init(pthread_cond_t *cond,pthread_condattr_t *attr);
  //	cond:	条件变量
  //	attr：	属性，通常置NULL
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);
  ret = pthread_create(&tid1, NULL, thr_boss, NULL);
  if (ret != 0) {
    printf("boss error\n");
    return -1;
  }
  ret = pthread_create(&tid2, NULL, thr_customer, NULL);
  if (ret != 0) {
    printf("boss error\n");
    return -1;
  }
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  //销毁条件变量
  //int pthread_cond_destroy(pthread_cond_t *cond);
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
  return 0;
}
