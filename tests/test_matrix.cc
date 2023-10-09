#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 3;
  bla::Matrix<double, bla::RowMajor> x(n, n);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      x(i, j) = i * n + j + 1;
    }
  }
  x(2, 2) = 10;

  std::cout << "x = " << x << std::endl;
  x.Transpose();
  std::cout << "x.Transpose() = " << x << std::endl;
  // std::cout << "x.GaussJordan() = " << x.GaussJordan() << std::endl;

  x(0, 2) = x(0, 2) / 3;
  std::cout << "x = " << x << std::endl;
}
