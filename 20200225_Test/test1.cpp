#include <iostream>

using namespace std;

int Add(int a, int b){
  int sum =  a + b;
  int* p = NULL;
  *p = 100;       // 注意：此处错误，对空指针进行解引用会导致段错误 
  return sum;
}

int Sum(int a, int b){
  return Add(a, b);
}

int main(){
  cout << Sum(10, 20) <<endl;
  return 0;
}
