#include <iostream>
#include <cstdlib>

unsigned long fact(unsigned long n){
  if(n==0) return 1;
  return n*fact(n-1);
}

unsigned long fact2(unsigned long x, unsigned long y=1){
  if(x==1) return y;
  return fact2(x-1,x*y);
}


const unsigned long  N=50;

int main(int argc, char** argv){
  std::cout << fact(N) << std::endl;
  std::cout << fact2(N) << std::endl;
  return EXIT_SUCCESS;
}


