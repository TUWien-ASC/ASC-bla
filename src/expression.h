#ifndef FILE_EXPRESSION_H
#define FILE_EXPRESSION_H


namespace ASC_bla
{

  template <typename T>
  class VecExpr
  {
  public:
   auto Upcast() const { return static_cast<const T&>(*this); }
   size_t Size() const { return Upcast().Size(); }
   auto operator()(size_t i) const { return Upcast()(i); }
   auto& operator()(size_t i) { return Upcast()(i); }
  };
  
 
  template <typename TA, typename TB>
  class SumVecExpr : public VecExpr<SumVecExpr<TA,TB>>
  {
    TA a_;
    TB b_;
  public:
    SumVecExpr (TA a, TB b) : a_(a), b_(b) { }
    auto Upcast() { return SumExpr(a_, b_); }

    auto operator() (size_t i) const { return a_(i)+b_(i); }
    size_t Size() const { return a_.Size(); }      
  };
  
  template <typename TA, typename TB>
  auto operator+ (const VecExpr<TA> & a, const VecExpr<TB> & b)
  {
    return SumVecExpr(a.Upcast(), b.Upcast());
  }

  template <typename TSCAL, typename TV>
  class ScaleVecExpr : public VecExpr<ScaleVecExpr<TSCAL, TV>> {
    TSCAL scal_;
    TV vec_;
  public:
    ScaleVecExpr (TSCAL scal, TV vec) : scal_(scal), vec_(vec) { }
    auto Upcast() { return ScalVecExpr(scal_, vec_); }

    auto operator() (size_t i) const { return scal_*vec_(i); }
    size_t Size() const { return vec_.Size(); }
  };

  template <typename T>
  auto operator* (double scal, const VecExpr<T> & v)
  {
    return ScaleVecExpr(scal, v.Upcast());
  }

  /****************************************************************/
  /*         My implementation of the matrix class                */
  /****************************************************************/

  template <typename T>
  class MatExpr {
   public:
    auto Upcast() const { return static_cast<const T&>(*this); }
    size_t SizeCols() const { return Upcast().SizeCols(); }
    size_t SizeRows() const { return Upcast().SizeRows(); }
    auto operator()(size_t i, size_t j) const { return Upcast()(i, j); }
    auto& operator()(size_t i, size_t j) { return Upcast()(i, j); }
  };

  template <typename TA, typename TB>
  class SumMatExpr : public MatExpr<SumMatExpr<TA, TB>> {
    TA a_;
    TB b_;

   public:
    SumMatExpr(TA a, TB b) : a_(a), b_(b) {}
    auto Upcast() { return SumExpr(a_, b_); }

    auto operator()(size_t i, size_t j) const { return a_(i, j) + b_(i, j); }
    size_t SizeCols() const { return a_.SizeCols(); }
    size_t SizeRows() const { return a_.SizeRows(); }
  };

  template <typename TA, typename TB>
  auto operator+(const MatExpr<TA>& a, const MatExpr<TB>& b) {
    return SumMatExpr<TA, TB>{a.Upcast(), b.Upcast()};
    // why not
    // return SumMatExpr(a.Upcast(), b.Upcast());
  }

  template <typename TSCAL, typename TM>
  class ScaleMatExpr : public MatExpr<ScaleMatExpr<TSCAL, TM>> {
    TSCAL scal_;
    TM mat_;

   public:
    ScaleMatExpr(TSCAL scal, TM mat) : scal_(scal), mat_(mat) {}
    auto Upcast() { return ScalMatExpr(scal_, mat_); }

    auto operator()(size_t i, size_t j) const { return scal_ * mat_(i, j); }
    size_t SizeCols() const { return mat_.SizeCols(); }
    size_t SizeRows() const { return mat_.SizeRows(); }
  };

  template <typename T>
  auto operator*(double scal, const MatExpr<T>& m) {
    return ScaleMatExpr<double, T>(scal, m.Upcast());
    // Why not ?
    //    return ScaleMatExpr(scal, m.Upcast());
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& ost, const VecExpr<T>& v) {
    if (v.Size() > 0) ost << v(0);
    for (size_t i = 1; i < v.Size(); i++) ost << ", " << v(i);
    return ost;
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& ost, const MatExpr<T>& m) {
    for (size_t i = 0; i < m.SizeRows(); i++) {
      for (size_t j = 0; j < m.SizeCols(); j++) {
        ost << m(i, j) << " ";
      }
      ost << std::endl;
    }
    return ost;
  }
}
 
#endif
