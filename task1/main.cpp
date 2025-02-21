#include "trie.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
  auto trie = Trie<char>();
  string str = "switch";
  string str2 = "switching";
  trie.insert(str);
  trie.insert(str2);
  trie.print();
}
