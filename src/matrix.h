/*
In this header file, we define a class template Matrix<T> that represents matrix
given 3 attributes: size_cols_ is the number of columns of the matrix,
size_rows_ is the number of rows of the matrix,
data_ is the entries of the matrix.

The class template Matrix<T> has 1 constructors:
Matrix(size_t size_rows, size_t size_cols) that takes as input the number of
rows and columns of the matrix and initializes the entries of the matrix to 0.

The class template Matrix<T> has 1 destructor:
~Matrix() that deletes the entries of the matrix.

The class template Matrix<T> has 1 copy constructor:
Matrix(const Matrix &m) that takes as input a matrix and copies the entries of
the matrix to the entries of the matrix.

The class template Matrix<T> has 1 move constructor:
Matrix(Matrix &&m) that takes as input a matrix and moves the entries of the
matrix to the entries of the matrix.

The class template Matrix<T> has 1 copy assignment operator:
Matrix &operator=(const Matrix &m2) that takes as input a matrix and copies the
entries of the matrix to the entries of the matrix.
*/

#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

namespace ASC_bla {

template <typename T> class Matrix {
    size_t size_cols_;
    size_t size_rows_;
    T **data_;

  public:
    Matrix(size_t size_rows, size_t size_cols)
        : size_rows_(size_rows), size_cols_(size_cols),
          data_(new T *[size_rows]) {
        ;
    }

    Matrix(const Matrix &m) : Matrix(m.SizeRows(), m.SizeCols()) { *this = m; }

    Matrix(Matrix &&m) : size_cols_{0}, size_rows_{0}, data_(nullptr) {
        std::swap(size_rows_, m.size_rows_);
        std::swap(size_cols_, m.size_cols_);
        std::swap(data_, m.data_);
    }

   Matrix() { delete[] data_; }

   Matrix &operator=(const Matrix &m2) {
       for (size_t i = 0; i < size_cols_; i++)
           for (size_t j = 0; j < size_rows_; j++)
               data_[i][j] = m2[i, j];
       return *this;
   }

   Matrix &operator=(Matrix &&m2) {
       for (size_t i = 0; i < size_; i++)
           data_[i] = m2(i);
       return *this;
   }

   size_t SizeRows() const { return size_rows_; }
   size_t SizeCols() const { return size_cols_; }
   T &operator[](size_t i, size_t j) { return data_[i][j]; }
   const T &operator[](size_t i, size_t j) const { return data_[i][j]; }
};

template <typename T>
Matrix<T>
operator+(const Matrix<T> &a, const Matrix<T> &b) {
    Matrix<T> sum(a.Size());
    for (size_t i = 0; i < a.Size(); i++)
        sum(i) = a(i) + b(i);
    return sum;
}

template <typename T>
std::ostream &
operator<<(std::ostream &ost, const Matrix<T> &v) {
    if (v.Size() > 0)
        ost << v(0);
    for (size_t i = 1; i < v.Size(); i++)
        ost << ", " << v(i);
    return ost;
}

}   // namespace ASC_bla

#endif
