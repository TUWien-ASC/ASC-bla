#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 10;
  bla::Matrix<double, bla::RowMajor> x(n, n), y(n, n);

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
  y = 1;
  // print the matrices
  std::cout << "Print the initial matrices" << std::endl;
  std ::cout << "x = " << x << std::endl;
  std ::cout << "y = " << y << std::endl;

  bla::Matrix<double, bla::RowMajor> z = x + y;
  bla::Matrix<double, bla::ColMajor> w(n, n);

  std::cout << "x+y = " << z << std::endl;
  //
  std::cout << "type of (x+3*y) is  " << typeid(x + 3 * y).name() << std::endl;

  z = x + 3 * y;
  std::cout << "type of (x+3*y) is  " << z << std::endl;
  //
  //// x.Range(2, 9) = 3;
  //// x.Slice(1, 5) = 10;
  //
  std::cout << "x = " << x << std::endl;
  // std::cout << "x.Transpose()= " << Transpose(x) << std::endl;
  std::cout << "x.Transpose()= " << Transpose(x) << std::endl;
  std::cout << "call transpose" << std::endl;

  w = Transpose(x);
  std::cout << "transpose is back" << std::endl;

  //  test x.Row(0)
  std::cout << "x.Row(0) = " << x.Row(0) << w.Row(0) << std::endl;
}
