#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

#include "expression.h"
#include "vector.h"

namespace ASC_bla {

template <typename T, ORDERING ORD,
          typename TDIST = std::integral_constant<size_t, 1>>
class MatrixView : public MatExpr<MatrixView<T, ORD, TDIST>, ORD> {
 protected:
  T* data_;
  size_t cols_;
  size_t rows_;
  TDIST dist_;

 public:
  MatrixView(size_t rows, size_t cols, T* data)
      : data_(data), rows_(rows), cols_(cols) {}

  MatrixView(size_t rows, size_t cols, TDIST dist, T* data)
      : data_(data), rows_(rows), cols_(cols), dist_(dist) {}

  template <typename TB>
  MatrixView& operator=(const MatExpr<TB, ORD>& m2) {
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < rows_; j++) {
        data_[dist_ * i + j] = m2(i, j);
      }
    }
    return *this;
  }

  MatrixView& operator=(T scal) {
    for (size_t i = 0; i < cols_ * rows_; i++) data_[dist_ * i] = scal;
    return *this;
  }

  auto View() const { return MatrixView(rows_, cols_, dist_, data_); }
  size_t SizeCols() const { return cols_; }
  size_t SizeRows() const { return rows_; }
  T& operator()(size_t i, size_t j) { return data_[dist_ * i + j]; }
  const T& operator()(size_t i, size_t j) const { return data_[dist_ * i + j]; }

  auto Row(size_t i) const {
    return VectorView<T, size_t>(cols_, dist_, data_ + i * dist_);
  }

  auto Col(size_t i) const {
    return VectorView<T, size_t>(rows_, dist_, data_ + i * dist_);
  }

  auto Rows(size_t first, size_t next) const {
    return MatrixView(next - first, cols_, dist_, data_ + first);
  }

  auto Cols(size_t first, size_t next) const {
    return MatrixView(rows_, next - first, dist_, data_ + first);
  }

  auto Transpose() const { return MatrixView(cols_, rows_, dist_, data_); }

  /*auto Inverse() const {
  MatrixView<T, size_t> eye(rows_, cols_, 1, data_);
  MatrixView<T, size_t> result(rows_, cols_, 1, data_);
  for (size_t i = 0; i < rows_; i++) {
    eye(i, i) = 1;
  }

  for (size_t i = 0; i < rows_; i++) {
    T pivot = result(i, i);

    // Make pivot element 1
    for (size_t j = 0; j < cols_; j++) {
      eye(i, j) = eye(i, j) / pivot;
      result(i, j) = result(i, j) / pivot;
    }

    for (size_t k = 0; k < rows_; k++) {
      if (k != i) {
        T factor = result(k, i);
        for (size_t j = 0; j < cols_; j++) {
          eye(k, j) = eye(k, j) - factor * eye(i, j);
          result(k, j) = result(k, j) - factor * result(i, j);
        }
      }
    }
  }
  return eye;
}*/
};

template <typename T, ORDERING ORD>
class Matrix : public MatrixView<T, ORD> {
  typedef MatrixView<T, ORD> BASE;
  using BASE::cols_;
  using BASE::data_;
  using BASE::rows_;

 public:
  Matrix(size_t rows, size_t cols)
      : MatrixView<T, ORD>(rows, cols, new T[rows * cols]) {
    ;
  }

  Matrix(const Matrix& m) : Matrix(m.SizeRows(), m.SizeCols()) { *this = m; }

  Matrix(Matrix&& m) : MatrixView<T, ORD>(0, 0, nullptr) {
    std::swap(cols_, m.cols_);
    std::swap(rows_, m.rows_);
    std::swap(data_, m.data_);
  }

  template <typename TB>
  Matrix(const MatExpr<TB, ORD>& m) : Matrix(m.SizeCols(), m.SizeRows()) {
    *this = m;
  }

  ~Matrix() { delete[] data_; }

  using BASE::operator=;
  Matrix& operator=(const Matrix& m2) {
    for (size_t i = 0; i < cols_; i++) {
      for (size_t j = 0; j < rows_; j++) {
        {
          data_[i + cols_ * j] = m2(i, j);
        }
      }
    }
    return *this;
  }

  Matrix& operator=(Matrix&& m2) {
    for (size_t i = 0; i < cols_; i++) {
      for (size_t j = 0; j < rows_; j++) {
        {
          data_[i + cols_ * j] = m2(i, j);
        }
      }
    }
    return *this;
  };
};

// output operator
// How to proèperly implement this? using ...Args?
template <typename T, ORDERING ORD>
std::ostream& operator<<(std::ostream& os, const Matrix<T, ORD>& m) {
  os << std::endl;
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

/*
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

 public:
  //
  void printData() {
    for (size_t i = 0; i < rows_ * cols_; i++) {
      std::cout << data_[i] << " ";
    }
  }
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
  ~Matrix() {
    std::cout << "destructor called" << std::endl;
    delete[] data_;
    std::cout << "destructor finished" << std::endl;
  }

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
    for (size_t i = 0; i < m2.SizeRows(); i++) {
      for (size_t j = 0; j < m2.SizeCols(); j++) {
        (*this)(i, j) = m2(i, j);
      }
    }
    return *this;
  }

  size_t SizeRows() const { return rows_; }
  size_t SizeCols() const { return cols_; }

  // Matrix-vector multiplication
  Vector<T> operator*(const Vector<T> &v) const {
    Vector<T> result(rows_);

    for (size_t i = 0; i < rows_; i++) {
      result(i) = 0;
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
        result(i, j) = 0;
      }
    }

    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < m.SizeCols(); j++) {
        for (size_t k = 0; k < cols_; k++) {
          result(i, j) = result(i, j) + (*this)(i, k) * m(k, j);
        }
      }
    }

    return result;
  }

  // operator () for element access
  T &operator()(size_t i, size_t j) {
    if (ORD == ColMajor) {
      return data_[i + cols_ * j];
    } else {
      return data_[j + rows_ * i];
    }
  }
  //
  const T &operator()(size_t i, size_t j) const {
    if (ORD == ColMajor) {
      return data_[i + this->cols_ * j];
    } else {
      return data_[j + this->rows_ * i];
    }
  }

  Matrix Transpose() {
    Matrix<T, ORD> result(this->cols_, this->rows_);
    for (size_t i = 0; i < this->SizeRows(); i++) {
      for (size_t j = 0; j < this->SizeCols(); j++) {
        result(j, i) = this->operator()(i, j);
      }
    }
    return result;
  }

  Matrix<T, ORD> GaussJordan() const {
    Matrix<T, ORD> eye(this->SizeRows(), this->SizeCols());
    for (size_t i = 0; i < this->SizeRows(); i++) {
      eye(i, i) = 1;
    }
    // Matrix<T, ORD> result(*this);
    Matrix<T, ORD> result(this->rows_, this->cols_);
    for (size_t i = 0; i < this->SizeRows(); i++) {
      for (size_t j = 0; j < this->SizeCols(); j++) {
        result(i, j) = this->operator()(i, j);
      }
    }

    // std::cout << result << std::endl;
    // std::cout << eye << std::endl;
    for (int i = 0; i < eye.SizeRows(); i++) {
      std::cout << "step i = " << i << std::endl;
      T pivot = result(i, i);

      // Make pivot element 1
      for (int j = 0; j < eye.SizeCols(); j++) {
        eye(i, j) = eye(i, j) / pivot;
        result(i, j) = result(i, j) / pivot;
      }

      for (size_t k = 0; k < eye.SizeRows(); k++) {
        if (k != i) {
          T factor = result(k, i);
          for (size_t j = 0; j < eye.SizeCols(); j++) {
            eye(k, j) = eye(k, j) - factor * eye(i, j);
            result(k, j) = result(k, j) - factor * result(i, j);
          }
        }
      }
      // std::cout << result << std::endl;
      // std::cout << eye << std::endl;
    }
    // std::cout << "ionveerse is = " << std::endl;
    // std::cout << eye << std::endl;
    return eye;
  };
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

*/