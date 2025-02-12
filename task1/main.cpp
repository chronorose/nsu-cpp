#include "treap.cpp"
#include <iostream>

using namespace std;

int main() {
  Treap<int, int>* t = new Treap<int, int>();
  t->insert(2, 5);
  t->insert(3, 30);
  t->print();
  cout << *t->remove(5) << endl;
  delete t;
}
