#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  pid_t pid = fork();
  if(pid == 0){
    printf("---child!! pid:[%d]\n",getpid());
  }
  else{
    printf("parent!!--- pid:[%d]\n",getpid());
  }
  while(1){
    printf("---pid:[%d]---\n",getpid());
    sleep(1);
  }
  return 0;
}
