#pragma once

#include <stdexcept>
#include <vector>

class SqMatrix;

class MatrixRow {
  friend class SqMatrix;
  std::vector<double> row;
  MatrixRow(size_t size) : row(size) {}

public:
  MatrixRow(const MatrixRow& other) = default;
  MatrixRow& operator=(const MatrixRow& another) = default;
  double& operator[](size_t index) { return row[index]; }
  const double& operator[](size_t index) const { return row[index]; }
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

  friend SqMatrix& operator+=(SqMatrix& lhs, const SqMatrix& rhs) {
    if (lhs.rows.size() != rhs.rows.size()) {
      throw std::invalid_argument(
          "You can only really sum only matrixes of the same size");
    }
    for (size_t i = 0; i < lhs.rows.size(); ++i) {
      for (size_t j = 0; j < lhs.rows.size(); ++j) {
        lhs.rows[i].row[j] += rhs.rows[i].row[j];
      }
    }
    return lhs;
  }

  SqMatrix(std::vector<double>& vec) : rows(vec.size(), MatrixRow(vec.size())) {
    for (size_t i = 0; i < vec.size(); ++i) {
      rows[i][i] = vec[i];
    }
  }

  MatrixRow& operator[](size_t index) { return rows[index]; }

  friend SqMatrix operator*(const SqMatrix& lhs, const SqMatrix& rhs) {
    if (lhs.rows.size() != rhs.rows.size()) {
      throw std::invalid_argument(
          "You can only really multiply only square matrixes of the same size");
    }
    SqMatrix res_matrix(lhs.rows.size());
    size_t size = lhs.rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        double sum = 0;
        for (size_t k = 0; k < size; ++k) {
          sum += lhs.rows[i].row[k] * rhs.rows[k].row[j];
        }
        res_matrix.rows[i].row[j] = sum;
      }
    }
    return res_matrix;
  }
  friend SqMatrix& operator*=(SqMatrix& lhs, const SqMatrix& rhs) {
    if (lhs.rows.size() != rhs.rows.size()) {
      throw std::invalid_argument(
          "You can only really multiply only square matrixes of the same size");
    }
    SqMatrix intermediate_matrix(lhs);
    size_t size = lhs.rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        double sum = 0;
        for (size_t k = 0; k < size; ++k) {
          sum += intermediate_matrix.rows[i].row[k] * rhs.rows[k].row[j];
        }
        lhs.rows[i].row[j] = sum;
      }
    }
    return lhs;
  }

  friend SqMatrix operator+(const SqMatrix& lhs, const SqMatrix& rhs) {
    if (lhs.rows.size() != rhs.rows.size()) {
      throw std::invalid_argument(
          "You can only really sum only matrixes of the same size");
    }
    SqMatrix res_matrix(lhs.rows.size());
    for (size_t i = 0; i < lhs.rows.size(); ++i) {
      for (size_t j = 0; j < lhs.rows.size(); ++j) {
        res_matrix[i][j] = lhs.rows[i].row[j] + rhs.rows[i].row[j];
      }
    }
    return res_matrix;
  }

  friend SqMatrix operator*(const SqMatrix& matrix, const double& other) {
    SqMatrix res_matrix(matrix.rows.size());
    size_t size = matrix.rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        res_matrix.rows[i].row[j] = matrix.rows[i].row[j] * other;
      }
    }
    return res_matrix;
  }
  friend SqMatrix& operator*=(SqMatrix& matrix, const double& other) {
    size_t size = matrix.rows.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        matrix.rows[i].row[j] = matrix.rows[i].row[j] * other;
      }
    }
    return matrix;
  }

  friend bool operator==(const SqMatrix& lhs, const SqMatrix& rhs) {
    if (lhs.rows.size() != rhs.rows.size())
      return false;
    for (size_t i = 0; i < lhs.rows.size(); ++i) {
      for (size_t j = 0; j < lhs.rows.size(); ++j) {
        if (lhs.rows[i].row[j] != rhs.rows[i].row[j]) {
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
