#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

#include "vector.h"  // Include the vector header file

namespace ASC_bla {

enum ORDERING { RowMajor, ColMajor };
template <typename T, ORDERING ORD>
class Matrix {
 private:
  size_t rows_;
  size_t cols_;
  T *data_;
  ORDERING ord_ = ORD;

 public:
  // Constructor
  Matrix(size_t rows, size_t cols)
      : rows_(rows), cols_(cols), data_(new T[rows * cols]), ord_(ORD) {
    ;
  }

  // Copy constructor
  Matrix(const Matrix &m)
      : Matrix(m.SizeRows(), m.SizeCols(), m.GetOrdering()) {
    *this = m;
  }

  // Move constructor
  Matrix(Matrix &&m) : rows_{0}, cols_{0}, data_(nullptr) {
    std::swap(rows_, m.rows_);
    std::swap(cols_, m.cols_);
    std::swap(data_, m.data_);
    std::swap(ord_, m.ord_);
  }

  // Destructor
  ~Matrix() { delete[] data_; }

  // Copy assignment operator
  Matrix &operator=(const Matrix &m2) {
    for (size_t i = 0; i < m2.SizeRows() * m2.SizeCols(); i++) {
      data_[i] = m2(i);
    }
    return *this;
  }

  Matrix &operator=(Matrix &&m2) {
    for (size_t i = 0; i < m2.SizeRows() * m2.SizeCols(); i++) {
      data_[i] = m2(i);
    }
    return *this;
  }

  size_t SizeRows() const { return rows_; }
  size_t SizeCols() const { return cols_; }

  Vector<T> operator*(const Vector<T> &v) const {
    if (cols_ != v.Size()) {
      throw std::invalid_argument("Matrix and vector dimensions do not match");
    }
    Vector<T> result(rows_);
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < cols_; j++) {
        result(i) += *this(i, j) * v(j);
      }
    }
    return result;
  }

  // Addition of matrices
  Matrix operator+(const Matrix &m) const {
    if (rows_ != m.SizeRows() || cols_ != m.SizeCols()) {
      throw std::invalid_argument(
          "Matrix dimensions do not match for addition");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < cols_; j++) {
        result(i, j) = (*this)(i, j) + m(i, j);
      }
    }

    return result;
  }
  // multiplication of matrices
  Matrix operator*(const Matrix &m) const {
    if (cols_ != m.SizeRows()) {
      throw std::invalid_argument(
          "Matrix dimensions do not match for multiplication");
    }

    Matrix result(rows_, m.SizeCols());
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < m.SizeCols(); j++) {
        for (size_t k = 0; k < cols_; k++) {
          result(i, j) += (*this)(i, k) * m(k, j);
        }
      }
    }

    return result;
  }

  // operator () for element access
  T &operator()(size_t i, size_t j) {
    if ((*this).GetOrdering() == ColMajor) {
      return data_[i + cols_ * j];
    } else {
      return data_[j + rows_ * i];
    }
  }

  const T &operator()(size_t i, size_t j) const {
    if ((*this).GetOrdering() == ColMajor) {
      return data_[i + cols_ * j];
    } else {
      return data_[j + rows_ * i];
    }
  }

  // Transpose: to create the transpose just invert the ordering and pass by
  // referece
  Matrix &Transpose() {
    if ((*this).GetOrdering() == ColMajor) {
      (*this).SetOrdering(RowMajor);
    } else {
      (*this).SetOrdering(ColMajor);
    }
    return *this;
  }

  ORDERING GetOrdering() const { return ord_; }

  void SetOrdering(ORDERING ord) { (*this).ord_ = ord; }
};

// Output operator
template <typename T, ORDERING ORD>
std::ostream &operator<<(std::ostream &os, const Matrix<T, ORD> &m) {
  for (size_t i = 0; i < m.SizeRows(); i++) {
    for (size_t j = 0; j < m.SizeCols(); j++) {
      os << m(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}

}  // namespace ASC_bla
#endif
