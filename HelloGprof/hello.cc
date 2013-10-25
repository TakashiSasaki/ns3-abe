#include <iostream>
#include <cstdlib>

int foo(){
  std::cout << "foo";
  srand(0);
  for(int i=0; i<1000000; ++i){
    //std::cout << rand();    
    rand();    
  }
  return 0;
}

int bar(){
  std::cout << "bar";
  return 1;
}

int main(int argc, char** argv){
  std::cout << foo();
  std::cout << bar();
  std::cout << foo();
  std::cout << bar();
  std::cout << foo();
  std::cout << "Hello" << std::endl;
  return EXIT_SUCCESS;
}
