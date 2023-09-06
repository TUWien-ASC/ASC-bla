#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

namespace ASC_bla
{

  template <typename T>
  class Matrix
  {
    size_t size_cols_;
    size_t size_rows_;
    T **data_;

  public:
    Matrix(size_t size)
        : size_rows_(size),
          size_cols_(size),
          data_(new T *[size]) { ; }

    Matrix(const Matrix &m)
        : Matrix(m.Size())
    {
      *this = v;
    }

   Matrix &&v)
        : size_{0}, data_(nullptr)
   {
     std::swap(size_, v.size_);
     std::swap(data_, v.data_);
   }

   Matrix() { delete[] data_; }

   Matrix &operator=(const Matrix &v2)
   {
     for (size_t i = 0; i < size_; i++)
       data_[i] = v2(i);
     return *this;
   }

   Matrix &operator= Matrix &&v2)
   {
     for (size_t i = 0; i < size_; i++)
       data_[i] = v2(i);
     return *this;
   }

   size_t Size() const { return size_; }
   T &operator()(size_t i) { return data_[i]; }
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
