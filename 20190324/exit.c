#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(){
  int pid = fork();
  if(pid <0){
    perror("fork errno");   //作用等同于下一行
    printf("fork errno :%s\n", strerror(errno));
  }
  int i = 0;
  for(; i < 256; ++i){
    printf("error:[%s]\n", strerror(i));
  }
}
