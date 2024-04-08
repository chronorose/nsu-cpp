#include "expr.hpp"

void test() {
    Expression* e = new Add(new Var("x"), new Mult(new Val(10), new Var("y")));
    Expression* e1 = e->diff("x");
    // Expression* e2 = e->diff("y");
    e->print();
    cout << endl;
    e1->print();
    // cout << endl;
    // e2->print();
    delete e;
    delete e1;
    // delete e2;
}

int main() {
    test();
}
