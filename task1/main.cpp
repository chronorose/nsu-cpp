#include <iostream>

typedef char byte

template<typename T> class AVLTree {
    T data;  
    AVLTree* parent;
    AVLTree* left;
    AVLTree* right;
    byte balance;
};

int main() {
    return 0;
}
