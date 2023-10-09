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
  // Default constructor
  Matrix(size_t rows, size_t cols)
      : rows_{rows}, cols_{cols}, data_{new T[rows * cols]} {}
  // Copy constructor
  Matrix(const Matrix &m) : Matrix(m.SizeRows(), m.SizeCols()) { *this = m; }

  // Move constructor
  Matrix(Matrix &&m) : rows_{0}, cols_{0}, data_(nullptr) {
    std::swap(rows_, m.rows_);
    std::swap(cols_, m.cols_);
    std::swap(data_, m.data_);
    // std::swap(ord_, m.ord_);
  }

  // Destructor
  ~Matrix() { delete[] data_; }

  // Copy assignment operator
  Matrix &operator=(const Matrix &m2) {
    for (size_t i = 0; i < m2.SizeRows(); i++) {
      for (size_t j = 0; j < m2.SizeCols(); j++) {
        (*this)(i, j) = m2(i, j);
      }
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
    if ((*this).GetOrdering() == RowMajor) {
      return data_[i + cols_ * j];
    } else {
      return data_[j + rows_ * i];
    }
  }

  const T &operator()(size_t i, size_t j) const {
    if ((*this).GetOrdering() == RowMajor) {
      return data_[i + this->SizeCols() * j];
    } else {
      return data_[j + this->SizeRows() * i];
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

  Matrix GaussJordan() const {
    if (this->SizeCols() != this->SizeRows()) {
      throw std::invalid_argument(
          "Matrix dimensions do not match for Gauss Elimination");
    }

    Matrix Augmented(this->SizeRows(), this->SizeCols() * 2);
    for (size_t i = 0; i < this->SizeRows(); i++) {
      for (size_t j = 0; j < this->SizeCols(); j++) {
        Augmented(i, j) = (*this)(i, j);
      }
    }
    for (size_t i = 0; i < this->SizeRows(); i++) {
      Augmented(i, i + this->SizeCols()) = 1;
    }

    for (size_t i = 0; i < this->SizeRows(); i++) {
      T aii = Augmented(i, i);
      for (size_t j = 0; j < this->SizeCols() * 2; j++) {
        Augmented(i, j) /= aii;
      }
      for (size_t k = 0; k < this->SizeRows(); k++) {
        if (k != i) {
          T aki = Augmented(k, i);
          for (size_t j = 0; j < this->SizeCols() * 2; j++) {
            Augmented(k, j) -= aki * Augmented(i, j);
          }
        }
      }
    }

    Matrix result(*this);

    for (size_t i = 0; i < result.SizeCols(); i++) {
      for (size_t j = 0; j < result.SizeRows(); j++) {
        result(i, j) = Augmented(i, j);
      }
    }

    return result;
  }
};

// Output operator
template <typename T, ORDERING ORD>
std::ostream &operator<<(std::ostream &os, const Matrix<T, ORD> &m) {
  os << std::endl;
  for (size_t i = 0; i < m.SizeRows(); i++) {
    for (size_t j = 0; j < m.SizeCols(); j++) {
      os << m(i, j) << " ";
    }
    os << std::endl;
  }
  return os;

}  // namespace ASC_bla

}  // namespace ASC_bla
#endif
