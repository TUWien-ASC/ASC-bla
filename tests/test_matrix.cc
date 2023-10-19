#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 10;
  bla::Matrix<double, bla::ColMajor> x(n, n), y(n, n), k(n, n );

  for (size_t i = 0; i < x.SizeCols(); i++) {
    for (size_t j = 0; j < x.SizeRows(); j++) {
      x(i, j) = 10 * i + j;
      y(i, i) = -2;
      if ((i != 0) && (i != n - 1)) {
        y(i, i - 1) = 1;
        y(i - 1, i) = 1;
        y(i, 1 + i) = 1;
        y(i + 1, i) = 1;
      }
    }
  }

  k = Inverse(y);

  std::cout << k << std::endl;

  std::cout << k*y<< std::endl;


  //
  //// x.Range(2, 9) = 3;
  //// x.Slice(1, 5) = 10;
  //
  std::cout << "x = " << x << std::endl;

  //  test x.Row(0)
  std::cout << "x.Row(0) = " << x.Row(0) << std::endl;

  //  test x.Col(0)
  std::cout << "x.Col(0) = " << x.Col(0) << std::endl;

  //  test x.Rows(0,2)
  std::cout << "x.Rows(0,2) = " << x.Rows(0, 2) << std::endl;

  //  test x.Cols(0,2)
  std::cout << "x.Cols(0,2) = " << x.Cols(0, 2) << std::endl;

  // create transpose matrix
  bla::Matrix<double, bla::ColMajor> xT = Transpose(x);
  std::cout << "xT = " << xT << std::endl;

  // test xT.Row(0
  std::cout << "xT.Row(0) = " << xT.Row(0) << std::endl;

  // test xT.Col(0)
  std::cout << "xT.Col(0) = " << xT.Col(0) << std::endl;

  // test xT.Rows(0,2)
  std::cout << "xT.Rows(0,2) = " << xT.Rows(0, 2) << std::endl;

  // test xT.Cols(0,2)
  std::cout << "xT.Cols(0,2) = " << xT.Cols(0, 2) << std::endl;

  // test xT.Rows(0,2).Cols(0,2)
  std::cout << "xT.Rows(0,2).Cols(0,2) = " << xT.Rows(0, 2).Cols(0, 2)
            << std::endl;

  // test xT.Cols(0,2).Rows(0,2)
  std::cout << "xT.Cols(0,2).Rows(0,2) = " << xT.Cols(0, 2).Rows(0, 2)
            << std::endl;

  std::cout << "multiplication by scalar" << std::endl;
  std::cout << "2 * x = " << 2 * x << std::endl;

  std::cout << "x = " << x << std::endl;
  std::cout << "y = " << y << std::endl;

  std::cout << "multiplication by matrix" << std::endl;
  std::cout << "x * y = " << x * x << std::endl;

  std::cout << "multiplication by vector" << std::endl;
  bla::Vector<double> v(n);
  for (size_t i = 0; i < v.Size(); i++) {
    v(i) = 1;
  }
  std::cout << "v = " << v << std::endl;
  std::cout << "x " << x << std::endl;
  std::cout << "x * v = " << x * v << std::endl;
}
