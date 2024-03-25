#include <iostream>
#include <optional>

using namespace std;

template <typename T>
class ScopedPointerDC {
    T* ptr = nullptr;
    public:
    ScopedPointerDC(T* raw_ptr): ptr(raw_ptr) {}
    ScopedPointerDC(const ScopedPointerDC& other) {
        ptr = new T;
        *ptr = *other.ptr;
    }
    ScopedPointerDC& operator=(const ScopedPointerDC& other) {
        if (this != &other) {
            if (ptr != nullptr) delete ptr;
            ptr = new T;
            *ptr = *other.ptr;
        }
        return *this;
    }
    ScopedPointerDC(ScopedPointerDC&& other) {
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    ScopedPointerDC& operator=(ScopedPointerDC&& other) {
        if (this != &other) {
            if (ptr != nullptr) delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    void set(T val) {
        *ptr = val;
    }
    optional<T> get() {
        if (ptr) return *ptr;
        return {};
    }
    ~ScopedPointerDC() {
        delete ptr;
    }
    bool operator==(const ScopedPointerDC& other) {
        if (ptr == other.ptr) return true;
        return false;
    }
};

template<typename T>
struct ScopedPointerOwn {
    T* ptr = nullptr;
    ScopedPointerOwn(T* raw): ptr(raw) {}
    ScopedPointerOwn(ScopedPointerOwn& other) {
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    ScopedPointerOwn& operator=(ScopedPointerOwn& other) {
        if (this != &other) {
            if (ptr) delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    // move constructors and move assignment is basically the same as copy in this context so no need to do them too;
    ~ScopedPointerOwn() {
        delete ptr;
    }
};

void tests() {
    int* s = new int(6);
    ScopedPointerDC<int> sp(s);
    int a = 30;
    // int* b = new int(a);
    sp.set(a);
    ScopedPointerDC<int> sp2 = sp;
    // sp = b;
    cout << *sp.get() << endl;
    cout << *sp2.get() << endl;
    if (sp == sp2) cout << " hell nahhh";
    else cout << "hell yeah";
}

int main() {
    tests();
    return 0;
}
