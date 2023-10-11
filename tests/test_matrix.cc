#include <matrix.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 10;
  bla::Matrix<double, bla::ColMajor> x(n, n), y(n, n);

  for (size_t i = 0; i < x.SizeCols(); i++) {
    for (size_t j = 0; j < x.SizeRows(); j++) {
      x(i, j) = i;
      y(i, j) = 10;
    }
  }

  bla::Matrix<double, bla::ColMajor> z = x + y;

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
}
