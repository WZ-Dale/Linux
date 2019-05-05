#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(){
  int pid = fork();
  if(pid < 0){
    perror("fork errno");
    exit(-1);
  }
  else if(pid == 0){
    sleep(5);
    exit(0);
  }
  //pid_t wait(int *status);
  //等待任意一个子进程退出
  //status:用于获取退出返回值
  //返回值:返回退出子进程的pid; 出错:返回-1
  int status;
  wait(&status);//等待子进程退出,等待5s之后子进程退出,开始damajiang
  while(1){
    printf("da ma jiang\n");
    sleep(1);
  }
  return 0;
}
