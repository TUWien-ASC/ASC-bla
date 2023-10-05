#ifndef FILE_VECTOR_H
#define FILE_VECTOR_H

#include <iostream>

namespace ASC_bla
{
  
  template <typename T>
  class Vector
  {
    size_t size_;
    T * data_;
    
  public:
    Vector (size_t size) 
      : size_(size), data_(new T[size]) { ; }
    
    Vector (const Vector & v)
      : Vector(v.Size())
    {
      *this = v;
    }

    Vector (Vector && v)
      : size_{0}, data_(nullptr)
    {
      std::swap(size_, v.size_);
      std::swap(data_, v.data_);
    }

    ~Vector () { delete [] data_; }
    
    Vector & operator=(const Vector & v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[i] = v2(i);
      return *this;
    }

    Vector & operator= (Vector && v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[i] = v2(i);
      return *this;
    }
    
    size_t Size() const { return size_; }
    T & operator()(size_t i) { return data_[i]; }
    const T & operator()(size_t i) const { return data_[i]; }
  };


  template <typename T>
  Vector<T> operator+ (const Vector<T> & a, const Vector<T> & b)
  {
    Vector<T> sum(a.Size());
    for (size_t i = 0; i < a.Size(); i++)
      sum(i) = a(i)+b(i);
    return sum;
  }
  
  template <typename T>
  std::ostream & operator<< (std::ostream & ost, const Vector<T> & v)
  {
    if (v.Size() > 0)
      ost << v(0);
    for (size_t i = 1; i < v.Size(); i++)
      ost << ", " << v(i);
    return ost;
  }
  
}

#endif
