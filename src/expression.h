#ifndef FILE_EXPRESSION_H
#define FILE_EXPRESSION_H


namespace ASC_bla
{

  template <typename T>
  class VecExpr
  {
  public:
    auto View() const { return static_cast<const T&> (*this); }
    size_t Size() const { return View().Size(); }
    auto operator() (size_t i) const { return View()(i); }
    auto & operator() (size_t i) { return  View()(i); }
  };
  
 
  template <typename TA, typename TB>
  class SumVecExpr : public VecExpr<SumVecExpr<TA,TB>>
  {
    TA a_;
    TB b_;
  public:
    SumVecExpr (TA a, TB b) : a_(a), b_(b) { }
    auto View () { return SumExpr(a_, b_); }

    auto operator() (size_t i) const { return a_(i)+b_(i); }
    size_t Size() const { return a_.Size(); }      
  };
  
  template <typename TA, typename TB>
  auto operator+ (const VecExpr<TA> & a, const VecExpr<TB> & b)
  {
    return SumVecExpr(a.View(), b.View());
  }

  template <typename TSCAL, typename TV>
  class ScaleVecExpr : public VecExpr<ScaleVecExpr<TSCAL, TV>> {
    TSCAL scal_;
    TV vec_;
  public:
    ScaleVecExpr (TSCAL scal, TV vec) : scal_(scal), vec_(vec) { }
    auto View () { return ScalVecExpr(scal_, vec_); }

    auto operator() (size_t i) const { return scal_*vec_(i); }
    size_t Size() const { return vec_.Size(); }
  };

  template <typename T>
  auto operator* (double scal, const VecExpr<T> & v)
  {
    return ScaleVecExpr(scal, v.View());
  }

  /****************************************************************/
  /*         My implementation of the matrix class                */
  /****************************************************************/
  enum ORDERING { RowMajor, ColMajor };
  template <typename T, ORDERING ORD>
  class MatExpr {
   public:
    auto View() const { return static_cast<const T&>(*this); }
    size_t SizeCols() const { return View().SizeCols(); }
    size_t SizeRows() const { return View().SizeRows(); }
    auto operator()(size_t i, size_t j) const { return View()(i, j); }
    auto& operator()(size_t i, size_t j) { return View()(i, j); }
  };

  template <typename TA, typename TB, ORDERING ORD>
  class SumMatExpr : public MatExpr<SumMatExpr<TA, TB, ORD>, ORD> {
    TA a_;
    TB b_;

   public:
    SumMatExpr(TA a, TB b) : a_(a), b_(b) {}
    auto View() { return SumExpr(a_, b_); }

    auto operator()(size_t i, size_t j) const { return a_(i, j) + b_(i, j); }
    size_t SizeCols() const { return a_.SizeCols(); }
    size_t SizeRows() const { return a_.SizeRows(); }
  };

  template <typename TA, typename TB, ORDERING ORD>
  auto operator+(const MatExpr<TA, ORD>& a, const MatExpr<TB, ORD>& b) {
    return SumMatExpr<TA, TB, ORD>{a.View(), b.View()};
    // why not
    // return SumMatExpr(a.View(), b.View());
  }

  template <typename TSCAL, typename TM, ORDERING ORD>
  class ScaleMatExpr : public MatExpr<ScaleMatExpr<TSCAL, TM, ORD>, ORD> {
    TSCAL scal_;
    TM mat_;

   public:
    ScaleMatExpr(TSCAL scal, TM mat) : scal_(scal), mat_(mat) {}
    auto View() { return ScalMatExpr(scal_, mat_); }

    auto operator()(size_t i, size_t j) const { return scal_ * mat_(i, j); }
    size_t SizeCols() const { return mat_.SizeCols(); }
    size_t SizeRows() const { return mat_.SizeRows(); }
  };

  template <typename T, ORDERING ORD>
  auto operator*(double scal, const MatExpr<T, ORD>& m) {
    return ScaleMatExpr<double, T, ORD>(scal, m.View());
    // Why not ?
    //    return ScaleMatExpr(scal, m.View());
  }
}
 
#endif
