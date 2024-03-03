#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Node {
    Node* prev;
    Node* next;
    Node* child;
    Node* parent;
    int value;
    int degree;
    bool marked;
    public:
    Node(int value): value(value), marked(false), degree(0), child(nullptr), parent(nullptr) {}
    Node(const Node& other): value(other.value), marked(other.marked), degree(other.degree), child(nullptr), parent(nullptr) {}
    friend class FHeap;
};

class FHeap {
    Node* heap;

    Node* singleton(int value) {
        Node* node = new Node(value);
        node->next = node->prev = node;
        return node;
    }

    Node* merge_(Node* n1, Node* n2) {
        if (n1 == nullptr) return n2;
        if (n2 == nullptr) return n1;

        if (n1->value > n2->value) {
            Node* tmp = n1;
            n1 = n2;
            n2 = tmp;
        }
        Node* n1next = n1->next;
        Node* n2prev = n2->prev;
        n1->next = n2;
        n2->prev = n1;
        n1next->prev = n2prev;
        n2prev->next = n1next;
        return n1;
    }

    Node* insert_(int value) {
        Node* ret = singleton(value);   
        heap = merge_(heap, ret);
        return ret;
    }

    void addChild(Node* parent, Node* child) {
        child->prev = child->next = child;
        child->parent = parent;
        parent->degree++;
        parent->child = merge_(parent->child, child);
    }

    void deleteHeap(Node* node) {
        if (node) {
            Node* holder = node;
            do {
                Node* rec = holder;
                holder = holder->next;
                deleteHeap(rec->child);
                delete rec;
            } while(holder != node);
        }
    }

    void unMark(Node* node) {
        if (node == nullptr) return;
        Node* holder = node;
        do {
            holder->marked = false;
            holder->parent = nullptr;
            holder = holder->next;
        } while (holder != node);
    }

    Node* removeMinimum(Node* node) {
        unMark(node->child);
        if (node->next == node) {
            node = node->child;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            node = merge_(node->next, node->child);
        }
        if (node == nullptr) return nullptr;
        vector<Node*>* trees = new vector<Node*>(node->degree + 4);
        while (true) {
            if (trees->at(node->degree) != nullptr) {
                Node* n = trees->at(node->degree);
                if (node == n) break;
                trees->at(node->degree) = nullptr;
                if (node->value < n->value) {
                    n->prev->next = n->next;
                    n->next->prev = n->prev;
                    addChild(node, n);
                } else {
                    n->prev->next = n->next;
                    n->next->prev = n->prev;
                    if (node->next == node) {
                        n->next = n->prev = n;
                        addChild(n, node);
                        node = n;
                    } else {
                        node->prev->next = n;
                        node->next->prev = n;
                        n->next = node->next;
                        n->prev = node->prev;
                        addChild(n, node);
                        node = n;
                    }
                }
                continue;
            } else {
                trees->at(node->degree) = node;
            }
            node = node->next;
        }
        Node* min = node;
        Node* start = node;
        do {
            if (node->value < min->value) 
                min = node;
            node = node->next;
        } while (node != start);
        delete trees;
        return min;
    }

    Node* cut(Node* heap, Node* node) {
        if (node->next == node) {
            node->parent->child = nullptr;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            node->parent->child = node->next;
        }
        node->next = node->prev = node;
        node->marked = false;
        return merge_(heap, node);
    }
    
    Node* decreaseKey_(Node* heap, Node* node, int value) {
        if(node->value < value) return heap;
        node->value = value;
        if (node->parent) {
            if (node->value < node->parent->value) {
                heap = cut(heap, node);
                Node* parent = node->parent;
                node->parent = nullptr;
                while(parent != nullptr && parent->marked) {
                    heap = cut(heap, parent);
                    node = parent;
                    parent = node->parent;
                    node->parent = nullptr;
                }
                if(parent != nullptr && parent->parent != nullptr) parent->marked = true;
            }
        } else {
            if (node->value < heap->value) {
                heap = node;
            }
        }
        return heap;
    }

    Node* copyTree(Node* node, Node* parent = nullptr) {
        if (node) {
            Node* holder = node;
            Node* newNode = new Node(*holder);                
            Node* originalNew = newNode;
            newNode->parent = parent;
            newNode->next = newNode;
            newNode->prev = newNode;
            newNode->child = copyTree(holder->child, newNode);
            holder = holder->next;
            while (holder != node) {
                Node* sibNode = new Node(*holder);
                sibNode->parent = parent;
                sibNode->prev = newNode;
                newNode->next = sibNode;
                sibNode->next = newNode->prev;
                sibNode->child = nullptr;
                sibNode->child = copyTree(holder->child, sibNode);
                newNode = sibNode;
                holder = holder->next;
            }
            newNode->next = originalNew;
            originalNew->prev = newNode;
            return originalNew;
        }
        return nullptr;
    }

    public:
    FHeap() {
        this->heap = nullptr;    
    }
    ~FHeap() {
        deleteHeap(this->heap);
    }
    FHeap& operator=(const FHeap& other) {
        this->deleteHeap(this->heap);
        this->heap = copyTree(other.heap);
        return *this;
    }
    FHeap(const FHeap& other) {
        this->heap = copyTree(other.heap);
    }
    int getMin() {
        return this->heap->value;
    }
    Node* insert(int value) {
        Node* ret = singleton(value);        
        this->heap = merge_(this->heap, ret);
        return ret;
    }
    void merge(FHeap* fheap) {
        this->heap = merge_(this->heap, fheap->heap);
        fheap->heap = nullptr;
    }
    int removeMin() {
        Node* heap = this->heap;
        this->heap = removeMinimum(this->heap);
        int ret = heap->value;
        delete heap;
        return ret;
    }
    void decreaseKey(Node* node, int value) {
        this->heap = decreaseKey_(this->heap, node, value);
    }
    void display() {
        if (this->heap == nullptr) {
            cout << "empty" << endl;
            return;
        }
        cout << "min: " << getMin() << endl;
        Node* holder = this->heap;
        do {
            displayTree(holder);
            holder = holder->next;
        } while(holder != heap);
        cout << endl;
    }
    void displayTree(Node* node) {
        cout << " -> ("<< node->value;
        if (node->child != nullptr) {
            Node* holder = node->child;
            do {
                cout << " -> " << holder->value;
                displayTree(holder);
                holder = holder->next;
            } while (holder != node->child);
        }
        cout << ")";
    }
};

void tests() {
    FHeap heap;
    heap.insert(32);
    heap.insert(14);
    heap.insert(13);
    heap.insert(21);
    heap.insert(121);
    heap.insert(5);
    heap.insert(33);
    heap.insert(37);
    heap.insert(39);
    heap.display();
    FHeap heap2 = heap;
    assert(heap.removeMin() == 5);
    heap.display();
    assert(heap.removeMin() == 13);
    heap.display();
    assert(heap.removeMin() == 14);
    heap.display();
    heap2.display();
}

int main() {
    tests();
}
