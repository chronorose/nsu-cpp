#include <iostream>

typedef char byte;


template<typename T> class AVLNode; 

template<typename T> class AVLTree {
    AVLNode<T>* root;
    public:
    AVLTree<T>() {
        this->root = nullptr;
    }
    void insert(T data) {
        AVLNode<T>* node = new AVLNode<T>(data);
        if(this->root == nullptr) {
            this->root = node;
        } else if(data < this->root->data) {
            this->root->left = insertNode(data, node, this->root->left);
        } else if(data > this->root->data) {
            this->root->right = insertNode(data, node, this->root->right);
        }
    }
    AVLNode<T>* insertNode(T data, AVLNode<T>* to_insert, AVLNode<T>* old) {
        
    }
};

template<typename T> class AVLNode {
    byte balance;
    public:
    T data; 
    AVLNode* left;
    AVLNode* right;
    AVLNode<T>(T data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->balance = 1;
    }
};

int main() {
    return 0;
}
