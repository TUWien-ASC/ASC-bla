#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 5;
  bla::Matrix<double, bla::RowMajor> x(n, n), y(n, n);
  bla::Matrix<double, bla::ColMajor> x2(n, n), y2(n, n);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      x(i, j) = j + i * n;
      y(i, j) = 10;
    }
  }

  bla::Matrix<double, bla::RowMajor> z = x + y;

  std::cout << "x+y = " << z << std::endl;
  std::cout << "x*y = " << (x * y).GetOrdering() << std::endl;
  std::cout << "x.GetOrdering()" << x2.GetOrdering() << std::endl;
  std::cout << "z.Transpose()" << z.Transpose() << std::endl;
}
