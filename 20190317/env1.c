#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[]){
  char *ptr = getenv("HOME");
  printf("HOME:[%s]\n", ptr);
  return 0;
}
