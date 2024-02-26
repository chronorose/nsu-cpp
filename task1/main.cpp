#include <iostream>

using namespace std;

class AVLTree {
    struct Node {
        int data;
        Node* left = nullptr;
        Node* right = nullptr;
        char balance;
        Node(int data) {
            this->data = data;
            this->balance = 0;
        }
    };

    Node* root = nullptr;

    char balance(Node* node) {
        return node == nullptr ? -1 : node->balance;
    }

    Node* insert(int data, Node* node) {
        if(node == NULL) {
            return new Node(data);
        } else if (data < node->data) {
            node->left = insert(data, node->left);
        } else if (data > node->data) {
            node->right = insert(data, node->right);
        }
        return node;
    }

    Node* rightRotate(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        node->balance = max(balance(node->left), balance(node->right)) + 1;
        leftl->balance = max(balance(left->left), balance(node->balance)) + 1;

    }    

    public:
    void insert(int data) {
        this->root = insert(data, this->root);
    }
}
