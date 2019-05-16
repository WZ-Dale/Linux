#include <stdio.h>
#include <unistd.h>
int main(){
  printf("parent pid: %d\n",getpid());
  int a = 100;
  //pid_t fork(void);
  pid_t pid = fork();
  if(pid < 0){
    return -1;
  }else if(pid == 0){
    printf("child!! pid: %d\n", getpid());
  }else{
    printf("parent!!: %d       ---child: %d\n", getpid(), pid);
  }
  printf("hello! %d\n", a);
  return 0;
}

