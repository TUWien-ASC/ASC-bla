#include <vector.h>

#include <iostream>

namespace bla = ASC_bla;

int main() {
  size_t n = 10;
  bla::Vector<double> x(n), y(n);

  for (size_t i = 0; i < x.Size(); i++) {
    x(i) = i;
    y(i) = 10;
  }

  bla::Vector<double> z = x + y;

  std::cout << "x+y = " << z << std::endl;

  std::cout << "type of (x+3*y) is  " << typeid(x + 3 * y).name() << std::endl;

  x.Range(2, 9) = 3;
  x.Slice(1, 5) = 10;

  std::cout << "x = " << x << std::endl;
}