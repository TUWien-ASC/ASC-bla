#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include "vector.h"   // Include the vector header file

namespace ASC_bla {

template <typename T>
class Matrix {
    size_t rows_;
    size_t cols_;
    Vector<Vector<T>> data_;

   public:
    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(new Vector<T>[rows]) {
        ;
    }

    // Copy constructor
    Matrix(const Matrix &m) : Matrix(m.SizeRows(), m.SizeCols()) { *this = m; }

    // Move constructor
    Matrix(Matrix &&m) : rows_{0}, cols_{0}, data_{Vector<T>(nullptr)} {
        std::swap(rows_, m.rows_);
        std::swap(cols_, m.cols_);
        std::swap(data_, m.data_);
    }

    // Destructor
    ~Matrix() { ; }   // delete[] data_; }

    // Copy assignment operator
    Matrix &operator=(const Matrix &m2) {
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                data_[i](j) = m2(i, j);
            }
        }
        return *this;
    }

    // Move assignment operator
    Matrix &operator=(Matrix &&m2) {
        for (size_t i = 0; i < rows_; i++) {
            data_[i] = m2(i);
        }
        return *this;
    }

    size_t SizeRows() const { return rows_; }

    size_t SizeCols() const { return cols_; }

    Vector<T> &operator()(size_t i) { return data_(i); }

    const Vector<T> &operator()(size_t i) const { return data_(i); }

    // Matrix-vector multiplication
    Vector<T> operator*(const Vector<T> &v) const {
        if (cols_ != v.Size()) {
            throw std::invalid_argument(
                "Matrix and vector dimensions do not match");
        }

        Vector<T> result(rows_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result(i) += data_[i](j) * v(j);
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
            result(i) = data_(i) + m(i);
        }

        return result;
    }

    // operator () for element access
    T &operator()(size_t i, size_t j) { return data_(i)(j); }
};

}   // namespace ASC_bla

#endif
