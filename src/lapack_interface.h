#ifndef FILE_LAPACK_INTERFACE_H
#define FILE_LAPACK_INTERFACE_H

#include <iostream>

#include "vector.h"



#include <complex>

typedef int integer;
typedef integer logical;
typedef float real;
typedef double doublereal;
typedef std::complex<float> singlecomplex;
typedef std::complex<double> doublecomplex;

// Windows SDK defines VOID in the file WinNT.h
#ifndef VOID
typedef void VOID;
#endif
typedef int ftnlen;
typedef int L_fp;  // ?


extern "C" {
#include <clapack.h>
}




namespace ASC_bla
{
  
  // BLAS-1 functions:

  /*
  int daxpy_(integer *n, doublereal *da, doublereal *dx, 
             integer *incx, doublereal *dy, integer *incy);
  */
  // y += alpha x
  template <typename SX, typename SY>
    void AddVectorLapack (double alpha, VectorView<double,SX> x, VectorView<double,SY> y)
  {
    integer n = x.Size();
    integer incx = x.Dist();
    integer incy = y.Dist();
    int err = 
      daxpy_ (&n, &alpha, &x(0),  &incx, &y(0), &incy);
    if (err != 0)
      std::cerr << "daxpy returned errcode " << err << std::endl;
  }
  
  
  // BLAS-2 functions:

  // BLAS-3 functions:
  
  /*
    int dgemm_ (char *transa, char *transb, integer *m, integer *
                n, integer *k, doublereal *alpha, doublereal *a, integer *lda, 
                doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, 
                integer *ldc);
  */

  /*
    // c = a*b
  template <ORDERING OA, ORDERING OB>
    void MultMatMatLapack (MatrixView<double, OA> a,
                           MatrixView<double, OB> b,
                           MatrixView<double, ColMajor> c)
  {
    char transa_ = (OA == ColMajor) ? 'N' : 'T';
    char transb_ = (OB == ColMajor) ? 'N' : 'T'; 
  
    integer n = c.Height();
    integer m = c.Width();
    integer k = a.Width();
    if (n == 0 || m == 0) return 0;
  
    double alpha = 1.0;
    double beta = 0;
    integer lda = a.Dist();
    integer ldb = b.Dist();
    integer ldc = c.Dist();

    int errc =
      dgemm_ (&transa_, &transb_, &n, &m, &k, &alpha, 
              a.Data(), &lda, b.Data(), &ldb, &beta, c.Data(), &ldc);

    if (err != 0)
      std::cerr << "daxpy returned errcode " << err << endl;
  }
                       
  template <ORDERING OA, ORDERING OB>
    int MultMatMatLapack (MatrixView<double, OA> a,
                          MatrixView<double, OB> b,
                          MatrixView<double, RowMajor> c)
  {
    MultMatMatLapack (Trans(b), Trans(a), Trans(c));
  }
  */
  
}


#endif
