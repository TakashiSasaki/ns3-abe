#include <iostream>
#include <cstdlib>

int foo(){
  return 0;
}

int bar(){
  return 1;
}

int main(int argc, char** argv){
  foo();
  bar();
  foo();
  foo();
  std::cout << "Hello" << std::endl;
  return EXIT_SUCCESS;
}
