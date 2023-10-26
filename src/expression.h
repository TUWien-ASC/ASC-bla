#ifndef FILE_EXPRESSION_H
#define FILE_EXPRESSION_H


namespace ASC_bla
{

  template <typename T>
    class Expr
    {
    public:
      auto View() const { return static_cast<const T&> (*this); }
      size_t Size() const { return View().Size(); }
      auto operator() (size_t i) const { return View()(i); }
      auto & operator() (size_t i) { return  View()(i); }
    };
  
  
  template <typename T, typename TDIST = std::integral_constant<size_t,1> >
  class VectorView : public Expr<VectorView<T,TDIST>>
  {
  protected:
    T * data_;
    size_t size_;
    TDIST dist_;
  public:
    VectorView (size_t size, T * data)
      : data_(data), size_(size) { }
    
    VectorView (size_t size, TDIST dist, T * data)
      : data_(data), size_(size), dist_(dist) { }
    
    template <typename TB>
    VectorView & operator= (const Expr<TB> & v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] = v2(i);
      return *this;
    }

    VectorView & operator= (T scal)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] = scal;
      return *this;
    }
    
    auto View() const { return VectorView(size_, dist_, data_); }
    size_t Size() const { return size_; }
    auto Dist() const { return dist_; }
    T & operator()(size_t i) { return data_[dist_*i]; }
    const T & operator()(size_t i) const { return data_[dist_*i]; }
    
    auto Range(size_t first, size_t next) const {
      return VectorView(next-first, dist_, data_+first);
    }

    auto Slice(size_t first, size_t slice) const {
      return VectorView<T,size_t> (size_/slice, dist_*slice, data_+first*dist_);
    }
      
  };
  
  
  template <typename TA, typename TB>
    class SumExpr : public Expr<SumExpr<TA,TB>>
    {
      TA a_;
      TB b_;
    public:
      SumExpr (TA a, TB b) : a_(a), b_(b) { }
      auto View () { return SumExpr(a_, b_); }

      auto operator() (size_t i) const { return a_(i)+b_(i); }
      size_t Size() const { return a_.Size(); }      
    };
  
  template <typename TA, typename TB>
    auto operator+ (const Expr<TA> & a, const Expr<TB> & b)
  {
    return SumExpr(a.View(), b.View());
  }



  
  template <typename TSCAL, typename TV>
    class ScaleExpr : public Expr<ScaleExpr<TSCAL,TV>>
    {
      TSCAL scal_;
      TV vec_;
    public:
      ScaleExpr (TSCAL scal, TV vec) : scal_(scal), vec_(vec) { }
      auto View () { return ScalExpr(scal_, vec_); }

      auto operator() (size_t i) const { return scal_*vec_(i); }
      size_t Size() const { return vec_.Size(); }      
    };
  
  template <typename T>
    auto operator* (double scal, const Expr<T> & v)
    {
      return ScaleExpr(scal, v.View());
    }

}
 
#endif
