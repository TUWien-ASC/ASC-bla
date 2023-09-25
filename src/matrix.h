#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

#include "vector.h"   // Include the vector header file

namespace ASC_bla {

template <typename T>
class Matrix {
   private:
    size_t rows_;
    size_t cols_;
    // Vector<Vector<T>> data_;
    T *data_;

   public:
    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(new T[rows * cols]) {
        ;
    }

    Matrix(const Matrix &m) : Matrix(m.SizeRows(), m.SizeCols()) { *this = m; }

    Matrix(Matrix &&m) : rows_{0}, cols_{0}, data_(nullptr) {
        std::swap(rows_, m.rows_);
        std::swap(cols_, m.cols_);
        std::swap(data_, m.data_);
    }

    ~Matrix() { delete[] data_; }
    Matrix &operator=(const Matrix &m2) {
        for (size_t i = 0; i < m2.cols_ * m2.rows_; i++) data_[i] = m2(i);
        return *this;
    }
    Matrix &operator=(Matrix &&m2) {
        for (size_t i = 0; i < cols_ * rows_; i++) data_[i] = m2(i);
        return *this;
    }

    size_t SizeRows() const { return rows_; }
    size_t SizeCols() const { return cols_; }

    Vector<T> operator*(const Vector<T> &v) const {
        if (cols_ != v.Size()) {
            throw std::invalid_argument(
                "Matrix and vector dimensions do not match");
        }

        Vector<T> result(rows_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result(i) += data_[i + cols_ * j] * v(j);
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
                result(i, j) = data_[i + cols_ * j] + m(i, j);
            }
        }

        return result;
    }

    // operator () for element access
    T &operator()(size_t i, size_t j) { return data_[i + cols_ * j]; }

    const T &operator()(size_t i, size_t j) const {
        return data_[i + cols_ * j];
    }

    // Transpose
    Matrix Transpose() const {
        Matrix result(cols_, rows_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result(j, i) = data_[i + cols_ * j];
            }
        }

        return result;
    }
};

template <typename T>
std::ostream &
operator<<(std::ostream &ost, const Matrix<T> &m) {
    if (m.SizeRows() > 0 && m.SizeCols() > 0) {
        for (size_t i = 0; i < m.SizeRows(); i++) {
            ost << m(i, 0);
            for (size_t j = 1; j < m.SizeCols(); j++) {
                ost << ", " << m(i, j);
            }
            ost << std::endl;
        }
    }
    return ost;
}

}   // namespace ASC_bla

#endif
