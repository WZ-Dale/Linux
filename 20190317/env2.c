#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[]){
  char *ptr = getenv("MYENV");
  printf("MYENV:[%s]\n", ptr);
  return 0;
}
