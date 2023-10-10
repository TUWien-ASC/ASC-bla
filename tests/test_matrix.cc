#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 2;

  std::cout << "test default constructor" << std::endl;
  bla::Matrix<double, bla::RowMajor> x(n, n);
  bla::Matrix<double, bla::RowMajor> y(n, n);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      x(i, j) = i * n + j + 1;
      y(i, j) = i * n + j + 1;
    }
  }

  std::cout << x << std::endl;

  // Test gaussian elimination
  std::cout << "test gaussian elimination" << std::endl;
  // std::cout << x << std::endl;
  y = x.GaussJordan();
  std::cout << y << std::endl;

  std::cout << x << std::endl;
  std::cout << x * y << std::endl;
}
