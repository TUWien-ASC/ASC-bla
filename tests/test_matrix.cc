#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 10;
  {
    bla::Matrix<long unsigned int, bla::ColMajor> x(n, n);
    bla::Matrix<long unsigned int, bla::ColMajor> y(n, n);
    //
    for (size_t i = 0; i < n; i++) {
      x(i, i) = 2;
      x(i, i + 1) = 1;
      x(i + 1, i) = 1;
    }

    std::cout << "print initial matrix" << std::endl;
    std::cout << x << std::endl;

    // Test gaussian elimination
    std::cout << "test gaussian elimination" << std::endl;
    y = x.GaussJordan();
    std::cout << "print inv" << std::endl;

    std::cout << y << std::endl;

    std::cout << "print orig" << std::endl;

    std::cout << x << std::endl;
    std::cout << "print prod" << std::endl;

    std::cout << x * y << std::endl;
  }
  std::cout << "fine" << std::endl;
  return 0;
}
