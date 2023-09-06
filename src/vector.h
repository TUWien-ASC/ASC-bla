#ifndef FILE_VECTOR_H // To check if the file has already been included
#define FILE_VECTOR_H // To mark that the file has now been included

#include <iostream> // For std::ostream

namespace ASC_bla // To avoid name clashes
{

  template <typename T> // T is a template parameter, in the compiler it is replaced by a type (int, float char...)
  class Vector
  {
    /*
      This class creates a vector of type T, which is a template parameter.
      size_ is the size of the vector,
      data_ is a pointer to the first element of the vector.
    */

    size_t size_; // size_t is a type that is guaranteed to be big enough to hold the size of any object, size_ is a member variable
    T *data_;     // data_ is a member variable

  public:
    Vector(size_t size) // Constructor
        : size_(size), data_(new T[size])
    {
      ;
    }

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
