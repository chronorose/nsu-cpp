#pragma once

#include <stdexcept>
#include <vector>

class MatrixRow {
  friend class SqMatrix;
  std::vector<double> row;
  MatrixRow(size_t size) : row(size) {}

public:
  MatrixRow(const MatrixRow& other) = default;
  MatrixRow& operator=(const MatrixRow& another) = default;
  double& operator[](size_t index) { return row[index]; }
};

class SqMatrix {
  std::vector<MatrixRow> rows;

public:
  SqMatrix(size_t size) : rows(size, MatrixRow(size)) {}
  SqMatrix() : SqMatrix(0) {}
  SqMatrix(const SqMatrix& other) = default;
  SqMatrix& operator=(const SqMatrix& other) = default;
  SqMatrix(SqMatrix&& other) = default;
  SqMatrix& operator=(SqMatrix&& other) = default;
  // there is room for improvement
  SqMatrix& operator+=(const SqMatrix& other) {
    if (rows.size() != other.rows.size()) {
      throw std::invalid_argument(
          "You can only really sum only matrixes of the same size");
    }
    for (size_t i = 0; i < rows.size(); ++i) {
      for (size_t j = 0; j < rows.size(); ++j) {
        rows[i].row[j] += other.rows[i].row[j];
      }
    }
    return *this;
  }
  SqMatrix(std::vector<double>& vec) : rows(vec.size(), MatrixRow(vec.size())) {
    for (size_t i = 0; i < vec.size(); ++i) {
      rows[i][i] = vec[i];
    }
  }
  MatrixRow& operator[](size_t index) { return rows[index]; }
  // there is room for improvement.
  SqMatrix operator+(const SqMatrix& other) const {
    if (rows.size() != other.rows.size()) {
      throw std::invalid_argument(
          "You can only really sum only matrixes of the same size");
    }
    SqMatrix res_matrix(rows.size());
    for (size_t i = 0; i < rows.size(); ++i) {
      for (size_t j = 0; j < rows.size(); ++j) {
        res_matrix[i][j] = rows[i].row[j] + other.rows[i].row[j];
      }
    }
    return res_matrix;
  }
  // there is room for improvement.
  SqMatrix operator*(const SqMatrix& other) const {
    if (rows.size() != other.rows.size()) {
      throw std::invalid_argument(
          "You can only really multiply only square matrixes of the same size");
    }
    SqMatrix res_matrix(rows.size());
    size_t size = rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        double sum = 0;
        for (size_t k = 0; k < size; ++k) {
          sum += rows[i].row[k] * other.rows[k].row[j];
        }
        res_matrix.rows[i].row[j] = sum;
      }
    }
    return res_matrix;
  }
  // yeah it's bad
  SqMatrix& operator*=(const SqMatrix& other) {
    if (rows.size() != other.rows.size()) {
      throw std::invalid_argument(
          "You can only really multiply only square matrixes of the same size");
    }
    SqMatrix intermediate_matrix(*this);
    size_t size = rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        double sum = 0;
        for (size_t k = 0; k < size; ++k) {
          sum += intermediate_matrix.rows[i].row[k] * other.rows[k].row[j];
        }
        rows[i].row[j] = sum;
      }
    }
    return *this;
  }
  SqMatrix operator*(const double& other) const {
    SqMatrix res_matrix(rows.size());
    size_t size = rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        res_matrix.rows[i].row[j] = rows[i].row[j] * other;
      }
    }
    return res_matrix;
  }
  SqMatrix& operator*=(const double& other) {
    size_t size = rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        rows[i].row[j] = rows[i].row[j] * other;
      }
    }
    return *this;
  }
  bool operator==(const SqMatrix& other) const {
    for (size_t i = 0; i < rows.size(); ++i) {
      for (size_t j = 0; j < rows.size(); ++j) {
        if (rows[i].row[j] != other.rows[i].row[j]) {
          return false;
        }
      }
    }
    return true;
  }
  bool operator!=(const SqMatrix& other) const { return !(*this == other); }
  explicit operator double() const {
    double sum = 0;
    for (size_t i = 0; i < rows.size(); ++i) {
      for (size_t j = 0; j < rows.size(); ++j) {
        sum += rows[i].row[j];
      }
    }
    return sum;
  }
};
