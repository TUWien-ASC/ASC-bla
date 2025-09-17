#ifndef FILE_VECTOR
#define FILE_VECTOR

#include <iostream>

#include "expression.hpp"


namespace ASC_bla
{
 
  template <typename T, typename TDIST = std::integral_constant<size_t,1> >
  class VectorView : public VecExpr<VectorView<T,TDIST>>
  {
  protected:
    T * data;
    size_t size;
    TDIST dist;
  public:
    VectorView (size_t _size, T * _data)
      : data(_data), size(_size) { }
    
    VectorView (size_t _size, TDIST _dist, T * _data)
      : data(_data), size(_size), dist(_dist) { }
    
    template <typename TB>
    VectorView & operator= (const VecExpr<TB> & v2)
    {
      for (size_t i = 0; i < size; i++)
        data[dist*i] = v2(i);
      return *this;
    }

    VectorView & operator= (T scal)
    {
      for (size_t i = 0; i < size; i++)
        data[dist*i] = scal;
      return *this;
    }
    
    auto View() const { return VectorView(size, dist, data); }
    size_t Size() const { return size; }
    T & operator()(size_t i) { return data[dist*i]; }
    const T & operator()(size_t i) const { return data[dist*i]; }
    
    auto Range(size_t first, size_t next) const {
      return VectorView(next-first, dist, data+first*dist);
    }

    auto Slice(size_t first, size_t slice) const {
      return VectorView<T,size_t> (size/slice, dist*slice, data+first*dist);
    }
      
  };
  
  

  
  template <typename T>
  class Vector : public VectorView<T>
  {
    typedef VectorView<T> BASE;
    using BASE::size;
    using BASE::data;
  public:
    Vector (size_t size) 
      : VectorView<T> (size, new T[size]) { ; }
    
    Vector (const Vector & v)
      : Vector(v.Size())
    {
      *this = v;
    }

    Vector (Vector && v)
      : VectorView<T> (0, nullptr)
    {
      std::swap(size, v.size);
      std::swap(data, v.data);
    }

    template <typename TB>
    Vector (const VecExpr<TB> & v)
      : Vector(v.Size())
    {
      *this = v;
    }
    
    ~Vector () { delete [] data; }

    using BASE::operator=;
    Vector & operator=(const Vector & v2)
    {
      for (size_t i = 0; i < size; i++)
        data[i] = v2(i);
      return *this;
    }

    Vector & operator= (Vector && v2)
    {
      for (size_t i = 0; i < size; i++)
        data[i] = v2(i);
      return *this;
    }
  };


  template <typename ...Args>
  std::ostream & operator<< (std::ostream & ost, const VectorView<Args...> & v)
  {
    if (v.Size() > 0)
      ost << v(0);
    for (size_t i = 1; i < v.Size(); i++)
      ost << ", " << v(i);
    return ost;
  }
  
}

#endif
