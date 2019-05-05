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
  int status;
  //pid_t waitpid(pid_t pid, int *ststus, int options);
  //pid: 指定的进程id
  //    -1:等待任意进程
  //    >0:等待指定子进程
  //status:用于获取返回值
  //options:选项
  //    WNOHANG:将waitpid设置为非阻塞
  //返回值: <0:出错   ==0:没有子进程退出    >0:退出子进程的pid
  //if(waitpid(pid,&status,0) < 0){
  //  perror("waitpid error");
  //}
  while(waitpid(pid,&status,WNOHANG) == 0){
    printf("no exit ~~ smoking ~~\n");
    sleep(1);
  }
  while(1){
    printf("da ma jiang\n");
    sleep(1);
  }
  return 0;
}
