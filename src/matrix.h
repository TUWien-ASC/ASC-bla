#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include "vector.h"

namespace ASC_bla
{

    enum ORDERING
    {
        ColMajor,
        RowMajor
    };
    template <typename T, ORDERING ORD>
    class Matrix
    {
        size_t rows_, cols_;
        Vector<T> data_;

    public:
        Matrix(size_t rows, size_t cols)
            : rows_(rows), cols_(cols), data_(rows * cols) {}

        Matrix(const Matrix &m)
            : Matrix(m.Rows(), m.Cols())
        {
            *this = m;
        }

        Matrix(Matrix &&m)
            : cols_{0}, rows_{0} data_(nullptr)
        {
            std::swap(rows_, m.rows_);
            std::swap(cols_, m.cols_);
            std::swap(data_, m.data_);
        }

        ~Matrix() {}

        Matrix &operator=(const Matrix &m2)
        {
            data_ = m2.Data();
            return *this;
        }

        Matrix &operator=(Matrix &&m2)
        {
            data_ = m2.Data();
            return *this;
        }
        Vector<T> Data() const { return data_; }
        size_t Rows() const { return rows_; }
        size_t Cols() const { return cols_; }
        T &operator()(size_t i, size_t j) { return data_[i]; }
        const T &operator()(size_t i) const { return data_[i]; }
    };

    template <typename T>
    Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
    {
        Matrix<T> sum(a.Size());
        for (size_t i = 0; i < a.Size(); i++)
            sum(i) = a(i) + b(i);
        return sum;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &ost, const Matrix<T> &v)
    {
        if (v.Size() > 0)
            ost << v(0);
        for (size_t i = 1; i < v.Size(); i++)
            ost << ", " << v(i);
        return ost;
    }

}

#endif
