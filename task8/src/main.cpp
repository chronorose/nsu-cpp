#include "reader.hpp"
#include "string.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  std::string s = "  7 71234    hello";
  char ch;
  std::string holder;
  int hi;
  StringReader r{s};
  r >> ch;
  r >> hi;
  r >> holder;
  std::cout << ch << " " << hi << " " << holder << std::endl;
  return 0;
}
