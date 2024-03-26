#include <iostream>
#include <vector>

using namespace std;

class Matrix {
    class Row {
        double* row = nullptr;
        Row() {}
        Row(size_t i) {
            row = new double[i]();
        }
        void init(size_t size) {
            if (row == nullptr) row = new double[size]();
        }
        ~Row() {
            delete[] row;
        }
        public:
        double& operator[](size_t i) {
            return row[i];
        }
        friend class Matrix;
    };
    Row* matrix;
    size_t size;
    public:
    Matrix(size_t size): size(size) {
        matrix = new Row[size];
        for (size_t i = 0; i < size; i++) {
            matrix[i].init(size);
        }
    }
    Matrix(vector<double>& vec): Matrix(vec.size()) {
        for(size_t i = 0; i < vec.size(); i++) {
            matrix[i].row[i] = vec.at(i);
        }
    }
    Row& operator[](size_t i) {
        return matrix[i];
    }
    ~Matrix() {
        delete[] matrix;
    }
};

int main() {
    vector<double> vec {1, 2, 3, 4, 5, 6};
    Matrix mat(vec);
    mat[0][1] = 3;
    cout << mat[0][1] << endl;
}
